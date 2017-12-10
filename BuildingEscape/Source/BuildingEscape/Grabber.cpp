// Copyright PD Enterprises 2018

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();

}

/// Look for Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber %s: No PhysicsHandle Found!"), *(GetOwner()->GetName()));
	}
}

/// Look for attached Input Component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber %s: InputComponent Found!"), *(GetOwner()->GetName()));

		/// Bind the Input Axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber %s: No InputComponent Found!"), *(GetOwner()->GetName()));
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// If physics handle is attached
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		/// Move the object we're holding
		PhysicsHandle->SetTargetLocation(GetTraceLineEndVector());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRAB"));

	/// Try and reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	AActor * ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (ActorHit && PhysicsHandle)
	{
		UPrimitiveComponent * ComponentToGrab = HitResult.GetComponent();
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None, // no bone
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true); // allow rotation
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("RELEASE"));
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

FVector UGrabber::GetTraceLineStartVector() const
{
	// Get Player Viewpoint
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Location, OUT Rotation);

	return Location;
}

FVector UGrabber::GetTraceLineEndVector() const
{
	// Get Player Viewpoint
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Location, OUT Rotation);

	return Location + (Rotation.Vector() * RaycastDistance);
}

FHitResult UGrabber::TraceLine(FVector VectorStart, FVector VectorEnd) const
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		VectorStart,
		VectorEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);

	return HitResult;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Raycast to reach distance
	auto HitResult = TraceLine(GetTraceLineStartVector(), GetTraceLineEndVector());

	/// Log Actor Hit
	AActor * HitActor = HitResult.GetActor();
	if (HitActor)
	{
		FString Name = HitActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Grabber HIT %s"), *Name);
	}

	return HitResult;
}