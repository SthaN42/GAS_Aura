// Copyright Nathan Guerin


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"

FString UAuraProjectileSpell::GetDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT("<Title>FIRE BOLT</>\n<Small>Level </><Level>%d</>\n\n<Default>Launches a bolt of fire, exploding on impact and dealing </><Damage>%d</><Default> fire damage with a chance to burn</>"), Level, Damage);
	}
	else
	{
		return FString::Printf(TEXT("<Title>FIRE BOLT</>\n<Small>Level </><Level>%d</>\n\n<Default>Launches %d bolts of fire, exploding on impact and dealing </><Damage>%d</><Default> fire damage with a chance to burn</>"), Level, FMath::Min(Level, MaxNumberOfProjectiles), Damage);
	}
}

FString UAuraProjectileSpell::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n<Small>Level </><Level>%d</>\n\n<Default>Launches %d bolts of fire, exploding on impact and dealing </><Damage>%d</><Default> fire damage with a chance to burn</>"), Level, FMath::Min(Level, MaxNumberOfProjectiles), Damage);
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

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;
	EffectContextHandle.AddHitResult(HitResult);
	
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}
	
	Projectile->DamageEffectSpecHandle = SpecHandle;

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
