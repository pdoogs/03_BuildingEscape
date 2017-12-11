// Copyright PD Enterprises 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileGunComponent.generated.h"

class UInputComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UProjectileGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UInputComponent* InputComponent = nullptr;
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	// Fires Projectile
	void Fire();

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float FireSpeed = 100; // TODO Reasonable default

	UPROPERTY(EditdefaultsOnly, Category = Projectile)
	float SpawnDistance = 100;
};
