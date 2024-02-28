// Copyright Nathan Guerin


#include "AbilitySystem/Abilities/AuraFireBlast.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> Fireballs;
	
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetAvatarActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();

		FireBall->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ExplosionDamageParams.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		
		Fireballs.Add(FireBall);

		FireBall->FinishSpawning(SpawnTransform);
	}
	
	return Fireballs;
}
