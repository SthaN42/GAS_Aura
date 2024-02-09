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
	 * @return The created DamageEffectParams
	 */
	UFUNCTION(BlueprintPure, meta = (AdvancedDisplay = 1))
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr, FVector InRadialDamageOrigin = FVector::ZeroVector) const;

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
