// Copyright Nathan Guerin


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"

FString UAuraProjectileSpell::GetDescription_Implementation(int32 Level)
{
	if (Level == 1)
	{
		return FString::Printf(TEXT("<Title>PROJECTILE</>\n<Small>Level </><Level>%d</>\n\n<Default>Launches a projectile, dealing damage on impact.</>"), Level);
	}
	else
	{
		return FString::Printf(TEXT("<Title>PROJECTILE</>\n<Small>Level </><Level>%d</>\n\n<Default>Launches %d projectiles, dealing damage on impact.</>"), Level, FMath::Min(Level, MaxNumberOfProjectiles));
	}
}

FString UAuraProjectileSpell::GetNextLevelDescription_Implementation(int32 Level)
{
	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n<Small>Level </><Level>%d</>\n\n<Default>Launches %d projectiles, dealing damage on impact.</>"), Level, FMath::Min(Level, MaxNumberOfProjectiles));
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, const bool bOverridePitch, const float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	Projectile->FinishSpawning(SpawnTransform);
}

float UAuraProjectileSpell::CalculatePitch(const float InitialProjectileSpeed, const FVector& StartLocation, const FVector& EndLocation, const float Gravity)
{
	const float SpeedSq = FMath::Square(InitialProjectileSpeed);
	const float SpeedPow4 = FMath::Pow(InitialProjectileSpeed, 4);
	const float DistanceToTarget = UE::Geometry::Distance(StartLocation, EndLocation);
	const float YDifference = EndLocation.Z - StartLocation.Z;
	const float DistanceSq = FMath::Square(DistanceToTarget);
	// This does NOT take air resistance into account. 
	return FMath::RadiansToDegrees(FMath::Atan((SpeedSq - FMath::Sqrt(SpeedPow4 - Gravity * (Gravity * DistanceSq + 2.f * YDifference * SpeedSq))) / (Gravity * DistanceToTarget)));
}
