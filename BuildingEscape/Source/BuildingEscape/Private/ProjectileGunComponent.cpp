// Copyright PD Enterprises 2018

#include "ProjectileGunComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UProjectileGunComponent::UProjectileGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileGunComponent::BeginPlay()
{
	Super::BeginPlay();

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!ensure(InputComponent)) return;

	InputComponent->BindAction("Fire", IE_Pressed, this, &UProjectileGunComponent::Fire);
	
}


// Called every frame
void UProjectileGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileGunComponent::Fire()
{
	//GetWorld()->SpawnActor<ProjectileClass>()
	UE_LOG(LogTemp, Warning, TEXT("FIRE"));
}