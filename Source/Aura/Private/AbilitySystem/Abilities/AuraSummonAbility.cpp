// Copyright Nathan Guerin


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations(bool bDrawDebugShapes)
{
	TArray<FVector> OutSpawnLocations;
	
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinionsToSpawn;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	
	for (int32 i = 0; i < NumMinionsToSpawn; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i + DeltaSpread / 2.f, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0, 0, 400.f), ChosenSpawnLocation - FVector(0, 0, 400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}

		OutSpawnLocations.Add(ChosenSpawnLocation);

		if (bDrawDebugShapes)
		{
			constexpr float DebugLifeTime = 300.f;
			DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 10.f, 12, FColor::Cyan, false, DebugLifeTime);
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Green, DebugLifeTime);
			
			// Min and Max possible spawn locations
			DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 5.f, 12, FColor::Red, false, DebugLifeTime);
			DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 5.f, 12, FColor::Red, false, DebugLifeTime);
		}
	}
	return OutSpawnLocations;
}
