// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/ItemPickup.h"


// Sets default values
AItemPickup::AItemPickup()
{
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(RootComponent);
	
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	PickupMesh->SetupAttachment(RootComponent);
	
	PickupMesh->SetCollisionProfileName("Interactable");
	
}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemPickup::Interact_Implementation(AActor* InteractingActor)
{
	
}





