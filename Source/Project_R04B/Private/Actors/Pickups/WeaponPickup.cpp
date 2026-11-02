// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Pickups/WeaponPickup.h"

#include "Components/InventoryComponent.h"
#include "Player/R04BPlayerState.h"
#include "RunetimeItems/Data/WeaponDataAsset.h"


// Sets default values
AWeaponPickup::AWeaponPickup()
{

}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponPickup::Interact_Implementation(AActor* InteractingActor)
{
	Super::Interact_Implementation(InteractingActor);
	PickupWeapon(InteractingActor);
}

void AWeaponPickup::PickupWeapon(AActor* InteractingActor)
{
	APawn* Pawn = Cast<APawn>(InteractingActor);
	APlayerState* PS = Pawn->GetPlayerState();
	AR04BPlayerState* State = Cast<AR04BPlayerState>(PS);
	UInventoryComponent* WeaponComponent = State->GetInventoryComponents();
	if (WeaponComponent->PickupWeapon(WeaponDataAsset, WeaponRuntimeData, bHasSavedRuntimeData))
	{
		Destroy();
	}
}


