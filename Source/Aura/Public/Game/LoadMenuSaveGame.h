// Copyright Nathan Guerin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadMenuSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ULoadMenuSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex = 0;

	UPROPERTY()
	FString SaveName = FString("Default Name");
};
