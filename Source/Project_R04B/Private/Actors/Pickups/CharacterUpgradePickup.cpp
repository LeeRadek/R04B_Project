// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/CharacterUpgradePickup.h"

#include "Actors/Characters/PlayableCharacters/BasePlayerChracter.h"
#include "Components/CharacterUpgradesComponent.h"
#include "Player/R04BPlayerState.h"


// Sets default values
ACharacterUpgradePickup::ACharacterUpgradePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ACharacterUpgradePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterUpgradePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterUpgradePickup::Interact_Implementation(AActor* InteractingActor)
{
	return ApplyCharacterUpgrade(InteractingActor);
	
}

void ACharacterUpgradePickup::ApplyCharacterUpgrade(AActor* InteractingActor)
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

	UCharacterUpgradesComponent* InventoryUpgrades = PS->FindComponentByClass<UCharacterUpgradesComponent>();
	if (!InventoryUpgrades)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState does not have a CharacterUpgradesComponent"));
		return;
	}
	int32 SlotIndex = INDEX_NONE;
	const bool bApplied = InventoryUpgrades->ApplyUpgrade(CharacterUpgradeData.UpgradeClass, SlotIndex);
	
	if (!bApplied)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to apply character upgrade: %s"), *GetName());
		return;
	}
	
	Destroy();
}

