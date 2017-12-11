// Copyright PD Enterprises 2018

#include "ProjectileGunComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"
#include "Public/DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UProjectileGunComponent::UProjectileGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UProjectileGunComponent::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if (!ensure(StaticMeshComponent)) return;

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
	if (!ensure(StaticMeshComponent)) return;
	if (!ensure(ProjectileClass)) return;

	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	auto SpawnLocation = PlayerLocation + PlayerRotation.Vector().GetSafeNormal() * SpawnDistance;
	auto SpawnRotation = PlayerRotation;

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation
		);

	if (!ensure(Projectile)) return;

	UE_LOG(LogTemp, Warning, TEXT("FIRE"));
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), SpawnLocation, FColor(0xff, 0, 0), true);

	// Launch Projectile
	Projectile->LaunchProjectile(FireSpeed);
}

