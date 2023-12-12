// Copyright Nathan Guerin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FireBolt")
	void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, const AActor* HomingTarget, const bool bOverridePitch = false, const float PitchOverride = 0.f);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	float ProjectileSpread = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (ClampMin = 1))
	int32 MaxNumberOfProjectiles = 5;

	UPROPERTY(EditDefaultsOnly, Category = "FireBolt")
	bool bLaunchHomingProjectiles = true;
	
	UPROPERTY(EditDefaultsOnly, Category = "FireBolt", meta = (EditCondition = "bLaunchHomingProjectiles"))
	float HomingAccelerationMin = 1600.f;

	UPROPERTY(EditDefaultsOnly, Category = "FireBolt", meta = (EditCondition = "bLaunchHomingProjectiles"))
	float HomingAccelerationMax = 3200.f;
};
