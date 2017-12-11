// Copyright PD Enterprises 2018

#include "FootstepsComponent.h"


// Sets default values for this component's properties
UFootstepsComponent::UFootstepsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFootstepsComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFootstepTime = GetWorld()->GetTimeSeconds();
	bPlayHasBegun = true;
	LastPosition = GetOwner()->GetActorLocation();
}


// Called every frame
void UFootstepsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bPlayHasBegun) return;

	// Have we moved?
	if (LastPosition.Equals(GetOwner()->GetActorLocation(), 0.01f)) { return; }
	LastPosition = GetOwner()->GetActorLocation();

	// Is it time for a footstep?
	if (GetWorld()->GetTimeSeconds() - LastFootstepTime < FootstepIntervalInSeconds) { return; }

	// Are we still on the ground?
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector Down = FVector(0, -1, 0);
	const FVector End = Start + Down * RaycastLength;

	/*
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters;
	if (GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		Start,
		End,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters))
		*/
	{
		LastFootstepTime = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("Footstep"));

		OnFootstep.Broadcast();
	}
}

