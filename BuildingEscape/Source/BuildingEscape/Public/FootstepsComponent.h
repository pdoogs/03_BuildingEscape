// Copyright PD Enterprises 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FootstepsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFootstepDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UFootstepsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootstepsComponent();

	UPROPERTY(BlueprintAssignable)
	FFootstepDelegate OnFootstep;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditdefaultsOnly, Category = "Footsteps")
	float RaycastLength = 300;

	UPROPERTY(EditDefaultsOnly, Category = "Footsteps")
	float FootstepIntervalInSeconds = 0.5f;

	float LastFootstepTime = 0.0f;

	bool bPlayHasBegun = false;

	FVector LastPosition;
	
};
