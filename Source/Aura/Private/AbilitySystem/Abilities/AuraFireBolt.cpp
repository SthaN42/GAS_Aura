// Copyright Nathan Guerin


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, AActor* HomingTarget, const bool bOverridePitch, const float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);

	// const int32 NumProjectiles = FMath::Min(MaxNumberOfProjectiles, GetAbilityLevel());
	
	// if (NumProjectiles > 1)
	if (MaxNumberOfProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (MaxNumberOfProjectiles - 1);
		// for (int32 i = 0; i < NumProjectiles; i++)
		for (int32 i = 0; i < MaxNumberOfProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			UKismetSystemLibrary::DrawDebugArrow(
				GetAvatarActorFromActorInfo(),
				SocketLocation + FVector(0, 0, 10),
				SocketLocation + FVector(0, 0, 10) + Direction * 75.f,
				5, FLinearColor::Red,
				120,
				1);
		}
	}
	else
	{
		UKismetSystemLibrary::DrawDebugArrow(
				GetAvatarActorFromActorInfo(),
				SocketLocation + FVector(0, 0, 10),
				SocketLocation + FVector(0, 0, 10) + Forward * 75.f,
				5, FLinearColor::Red,
				120,
				1);
	}

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.f, 5, FLinearColor::White, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.f, 5, FLinearColor::Gray, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.f, 5, FLinearColor::Gray, 120, 1);
}
