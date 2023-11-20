// Copyright Nathan Guerin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations(bool bDrawDebugShapes);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Summoning")
	int32 NumMinionsToSpawn = 5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 50.f;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.f;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Summoning")
	float SpawnSpread = 90.f;
};
