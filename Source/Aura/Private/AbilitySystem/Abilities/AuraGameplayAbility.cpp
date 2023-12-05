// Copyright Nathan Guerin


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDescription_Implementation(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription_Implementation(int32 Level)
{
	return FString::Printf(TEXT("<Default>Next Level: </><Level>%d</>\n<Default>Causes mush more damage</>"), Level);
}

FString UAuraGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked Until</>\n<Small>Level </><Level>%d</>"), Level);
}
