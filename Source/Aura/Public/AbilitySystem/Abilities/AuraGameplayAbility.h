// Copyright Nathan Guerin

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Descriptions")
	FString GetDescription(int32 Level);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Descriptions")
	FString GetNextLevelDescription(int32 Level);
	
	static FString GetLockedDescription(int32 Level);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (Categories = "Input"))
	FGameplayTag StartupInputTag;

protected:
	UFUNCTION(BlueprintPure)
	float GetManaCost(float InLevel = 1.f) const;
	
	UFUNCTION(BlueprintPure)
	float GetCooldown(float InLevel = 1.f) const;
};
