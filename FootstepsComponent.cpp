// Copyright PD Enterprises 2018

#include "FootstepsComponent.h"


// Sets default values
AFootstepsComponent::AFootstepsComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFootstepsComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFootstepTime = GetWorld()->GetTimeSeconds();
}

// Called every frame
void AFootstepsComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Are we moving?
	FVector Velocity = GetOwner()->GetVelocity();
	if (FVector::DotProduct(Velocity, Velocity) < 0.001f) { return; }

	// Is it time for a footstep?
	if (GetWorld()->GetTimeSeconds() - FootstepIntervalInSeconds <= LastFootstepTime) { return; }

	// Are we still on the ground?
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector Down = FVector(0, -1, 0);
	const FVector End = Start + Down * RaycastLength;

	FHitResult HitResult;
	FCollisionQueryParams TraceParameters;
	if (GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		Start,
		End,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters))
	{
		LastFootstepTime = GetWorld()->GetTimeSeconds();

		OnFootstep.Broadcast();
	}
}

