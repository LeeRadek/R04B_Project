// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/WeaponUpgradePickup.h"
#include "GameFramework/PlayerState.h"
#include "Components/InventoryComponent.h"
#include "Logs/ProjectLogs.h"


// Sets default values
AWeaponUpgradePickup::AWeaponUpgradePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponUpgradePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponUpgradePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponUpgradePickup::Interact_Implementation(AActor* InteractingActor)
{
	return ApplyWeaponUpgrade(InteractingActor);
}

void AWeaponUpgradePickup::ApplyWeaponUpgrade(AActor* InteractingActor)
{
	if (!InteractingActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid InteractingActor provided to Interact_Implementation"));
		//temp log later add a log category for this
		return;
	}
	
	APawn* Pawn = Cast<APawn>(InteractingActor);
	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractingActor is not a BasePlayerChracter"));
		return;
	}
	
	APlayerState* PS = Pawn->GetPlayerState<APlayerState>();
	if (!PS)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState is not a PlayerState"));
		return;
	}
	
	UInventoryComponent* Inventory = PS->FindComponentByClass<UInventoryComponent>();
	if (!Inventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent not found on PlayerState"));
		return;
	}
	
	if (!UpgradeClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid UpgradeClass provided to ApplyWeaponUpgrade"));
		return;
	}
	
	bool bSuccess = Inventory->PickupUpgrade(UpgradeClass);
	
	if (bSuccess)
	{
		Destroy();
	}

}

