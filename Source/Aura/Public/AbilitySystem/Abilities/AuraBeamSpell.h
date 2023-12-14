// Copyright Nathan Guerin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraBeamSpell.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraBeamSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Beam Spell")
	void StoreMouseDataInfo(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintCallable, Category = "Beam Spell")
	void StoreOwnerVariables();

	UFUNCTION(BlueprintCallable, Category = "Beam Spell")
	void TraceFirstTarget(const FVector& BeamTargetLocation, const bool bDrawDebugVolumes = false);

	UFUNCTION(BlueprintCallable, Category = "Beam Spell")
	void StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Beam")
	int32 MaxNumberOfShockTargets = 5;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Beam")
	float AdditionalShockTargetsMaxDistance = 850.f;
	
	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<AActor> MouseHitActor;

	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "Beam")
	TObjectPtr<APlayerController> OwnerPlayerController;
};
