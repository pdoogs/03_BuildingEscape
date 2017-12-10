// Copyright PD Enterprises 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	check(Owner != nullptr);

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Pressure Plate"), *(GetOwner()->GetName()));
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll trigger volume every frame
	// If ActorThatOpens is in the volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) // TODO make into parameter
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	if (!PressurePlate) return 0.0f;

	float TotalMass = 0.0f;
	
	// Find all overlapping actors
	TSet<AActor*> ActorSet;
	PressurePlate->GetOverlappingActors(OUT ActorSet);

	// For each actor
	for (const AActor * Actor : ActorSet)
	{
		// Accumulate weight
		UPrimitiveComponent * PrimitiveComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
		if (PrimitiveComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("OpenDoor Found Primitive Component %s"), *(Actor->GetName()));
			TotalMass += PrimitiveComponent->GetMass();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Mass = %f"), TotalMass);

	return TotalMass;
}