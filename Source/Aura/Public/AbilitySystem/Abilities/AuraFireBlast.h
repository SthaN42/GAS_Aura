// Copyright Nathan Guerin

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraFireBlast.generated.h"

class AAuraFireBall;
/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBlast : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<AAuraFireBall*> SpawnFireBalls();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireBlast", DisplayName = "Number of Fire Balls")
	int32 NumFireBalls = 12;

private:
	UPROPERTY(EditDefaultsOnly, Category = "FireBlast")
	TSubclassOf<AAuraFireBall> FireBallClass;
};
