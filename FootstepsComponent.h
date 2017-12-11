// Copyright PD Enterprises 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FootstepsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFootstepDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API AFootstepsComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFootstepsComponent();

	FFootstepDelegate OnFootstep;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditdefaultsOnly, Category = "Footsteps")
	float RaycastLength = 300;

	UPROPERTY(EditDefaultsOnly, Category = "Footsteps")
	float FootstepIntervalInSeconds = 2;

	float LastFootstepTime = 0.0f;
};
