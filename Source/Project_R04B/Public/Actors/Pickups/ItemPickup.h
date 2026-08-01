// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewportInteractableInterface.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "ItemPickup.generated.h"

class USphereComponent;

UCLASS()
class PROJECT_R04B_API AItemPickup : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemPickup();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Pickup")
	bool bIsNewWeapon = true;

protected:

	//----------------------- Variables ---------------------//
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon Pickup")
	TObjectPtr<UStaticMeshComponent> PickupMesh;
	
	
	//----------------------- Native Functions ---------------------//
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation(AActor* InteractingActor) override;
	
	//---------------------- Functions ---------------------//


public:
	
	
};
