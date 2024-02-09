// Copyright Nathan Guerin

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	/**
	 * Creates DamageEffectParams using the class defaults
	 * @param TargetActor The actor that is targeted by this ability
	 * @param InRadialDamageOrigin If IsRadialDamage is true, the DamageEffectParams needs the origin to compute the radial damage
	 * @param bOverrideKnockbackDirection If True, we'll take the provided knockback direction instead of computing it based on the direction of the owning actor
	 * @param KnockbackDirectionOverride The direction the target will be pushed towards if there was a knockback
	 * @param bOverrideDeathImpulseDirection If True, we'll take the provided death impulse direction instead of computing it based on the direction of the owning actor
	 * @param DeathImpulseDirectionOverride The direction the target will be pushed towards if this damage was fatal
	 * @param bOverridePitch If True, we'll take the provided pitch angle for the knockback instead of the default 45 degrees
	 * @param PitchOverride The pitch the target will be pushed toward if there was a knockback
	 * @return The created DamageEffectParams
	 */
	UFUNCTION(BlueprintPure, meta = (AdvancedDisplay = 1))
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr,
		FVector InRadialDamageOrigin = FVector::ZeroVector,
		bool bOverrideKnockbackDirection = false,
		FVector KnockbackDirectionOverride = FVector::ZeroVector,
		bool bOverrideDeathImpulseDirection = false,
		FVector DeathImpulseDirectionOverride = FVector::ZeroVector,
		bool bOverridePitch = false,
		float PitchOverride = 0.f) const;

protected:
	UFUNCTION(BlueprintPure)
	float GetDamage(const float InLevel = 1.f) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (Categories = "Damage"))
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage|Forces and impulses")
	float KnockbackChance = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage|Forces and impulses")
	float KnockbackForceMagnitude = 500.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage|Forces and impulses")
	float DeathImpulseMagnitude = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage|Debuff")
	float DebuffChance = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage|Debuff")
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage|Debuff")
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage|Debuff")
	float DebuffDuration = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage|Radial")
	bool bIsRadialDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage|Radial")
	float RadialDamageInnerRadius = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage|Radial")
	float RadialDamageOuterRadius = 0.f;
};
