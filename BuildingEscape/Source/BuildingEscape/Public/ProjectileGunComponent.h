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
	
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	void Fire();
};
