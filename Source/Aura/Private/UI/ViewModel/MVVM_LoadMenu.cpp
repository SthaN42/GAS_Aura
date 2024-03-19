// Copyright Nathan Guerin


#include "UI/ViewModel/MVVM_LoadMenu.h"

#include "Game/AuraGameModeBase.h"
#include "Game/LoadMenuSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadMenu::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_0->SetLoadSlotName(FString("LoadSlot_0"));
	LoadSlot_0->SlotIndex = 0;
	LoadSlots.Add(0, LoadSlot_0);
	
	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_1->SetLoadSlotName(FString("LoadSlot_1"));
	LoadSlot_1->SlotIndex = 1;
	LoadSlots.Add(1, LoadSlot_1);
	
	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_2->SetLoadSlotName(FString("LoadSlot_2"));
	LoadSlot_2->SlotIndex = 2;
	LoadSlots.Add(2, LoadSlot_2);
}

void UMVVM_LoadMenu::LoadData()
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	for (const TTuple<int32, UMVVM_LoadSlot*> LoadSlot : LoadSlots)
	{
		const ULoadMenuSaveGame* SaveObject = AuraGameMode->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(), LoadSlot.Key);

		LoadSlot.Value->SetSaveName(SaveObject->SaveName);
		LoadSlot.Value->SlotStatus = SaveObject->SaveSlotStatus;
		LoadSlot.Value->SetMapName(SaveObject->MapName);

		LoadSlot.Value->InitializeSlot();
	}
}

UMVVM_LoadSlot* UMVVM_LoadMenu::GetLoadSlotViewModelByIndex(const int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadMenu::NewSlotButtonPressed(const int32 Slot, const FString& EnteredName)
{
	//TODO: When play-testing from the LoadMenu map, this always fails to get the game mode. We should be able to get it though, should fix this 
	const AAuraGameModeBase* AuraGameMode = CastChecked<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));

	LoadSlots[Slot]->SetSaveName(EnteredName);
	LoadSlots[Slot]->SlotStatus = Taken;
	LoadSlots[Slot]->SetMapName(AuraGameMode->DefaultMapName);

	AuraGameMode->SaveSlotData(LoadSlots[Slot], Slot);

	LoadSlots[Slot]->InitializeSlot();
}

void UMVVM_LoadMenu::NewGameButtonPressed(const int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadMenu::SelectSlotButtonPressed(const int32 Slot)
{
	SlotSelected.Broadcast();
	
	// Enable the selected slot button, and disable the others
	for (const TTuple<int32, UMVVM_LoadSlot*> LoadSlot : LoadSlots)
	{
		LoadSlot.Value->EnableSelectSlotButton.Broadcast(LoadSlot.Key != Slot);
	}

	SelectedSlotIndex = Slot;
}

void UMVVM_LoadMenu::DeleteButtonPressed()
{
	if (IsValid(LoadSlots[SelectedSlotIndex]))
	{
		AAuraGameModeBase::DeleteSlot(LoadSlots[SelectedSlotIndex]->GetLoadSlotName(), SelectedSlotIndex);
		LoadSlots[SelectedSlotIndex]->SlotStatus = Vacant;
		LoadSlots[SelectedSlotIndex]->InitializeSlot();
		LoadSlots[SelectedSlotIndex]->EnableSelectSlotButton.Broadcast(true);
	}
}
