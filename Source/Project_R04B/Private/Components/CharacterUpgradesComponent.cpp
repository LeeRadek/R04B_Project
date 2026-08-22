// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterUpgradesComponent.h"

#include "Logs/ProjectLogs.h"
#include "RunetimeItems/CharacterUpgrade.h"
#include "Components/InventoryComponent.h"
#include "Player/R04BPlayerState.h"
#include "Actors/Characters/PlayableCharacters/BasePlayerChracter.h"

// Sets default values for this component's properties
UCharacterUpgradesComponent::UCharacterUpgradesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CharacterUpgrades.SetNum(3); // Initialize size for 5 upgrades, can be modified later to allow for dynamic upgrade sizes

}


// Called when the game starts
void UCharacterUpgradesComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningPlayerState = Cast<AR04BPlayerState>(GetOwner());
	OwningPlayer = OwningPlayerState ? OwningPlayerState->GetCharacter() : nullptr;
	// ...
	
}


// Called every frame
void UCharacterUpgradesComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

bool UCharacterUpgradesComponent::IsEnoughDataToApplyUpgrade(TSubclassOf<UCharacterUpgrade> Upgrade, float& MissingData) const
{
	if (!Upgrade)
	{
		UE_LOG(LogCharacterUpgradeComponent, Warning, TEXT("Invalid Upgrade provided to IsEnoughDataToApplyUpgrade"));
		return false;
	}
	
	const UCharacterUpgrade* CharacterUpgradeCDO = Upgrade->GetDefaultObject<UCharacterUpgrade>();
	
	const float DataToActiveUpgrade = CharacterUpgradeCDO->DataToActiveUpgrade;
	float FinalDataToApply = CharacterData + DataToActiveUpgrade;
	
	if (LockedCharacterData - FinalDataToApply >= 0.0f)
	{
		MissingData = LockedCharacterData - FinalDataToApply;
		return true;
	}
	else
	{
		MissingData = FinalDataToApply - LockedCharacterData;
	}
	
	return false;
}

UCharacterUpgrade* UCharacterUpgradesComponent::CreateCharacterUpgrade(
	TSubclassOf<UCharacterUpgrade> UpgradeClass)
{
	if (!UpgradeClass)
	{
		UE_LOG(LogCharacterUpgradeComponent, Error, TEXT("Invalid Upgrade Class"));
		return nullptr;
	}
	
	UCharacterUpgrade* NewUpgrade = NewObject<UCharacterUpgrade>(this, UpgradeClass);
	UInventoryComponent* WeaponInventoryComponent = OwningPlayerState->GetInventoryComponents();
	
	NewUpgrade->InitializeUpgrade(OwningPlayer, this, WeaponInventoryComponent, OwningPlayerState);
	
	return NewUpgrade;
}

bool UCharacterUpgradesComponent::ApplyUpgrade(TSubclassOf<UCharacterUpgrade> Upgrade, int32& OutIndex)
{
	if (!Upgrade)
	{
		UE_LOG(LogCharacterUpgradeComponent, Warning, TEXT("Invalid Upgrade provided to ApplyUpgrade"));
		OutIndex = INDEX_NONE;
		return false;
	}
	
	UCharacterUpgrade* NewUpgrade = CreateCharacterUpgrade(Upgrade);
	
	if (!NewUpgrade)
	{
		return false;
	}
	
	return AddToUpgradesArray(NewUpgrade, OutIndex);
}

UCharacterUpgrade* UCharacterUpgradesComponent::RemoveUpgrade(UCharacterUpgrade* Upgrade)
{
	if (!Upgrade)
	{
		UE_LOG(LogCharacterUpgradeComponent, Warning, TEXT("Invalid Upgrade provided to RemoveUpgrade"));
		return nullptr;
	}
	
	UnlockUsedCharacterData(Upgrade->DataToActiveUpgrade);
	Upgrade->OnRemoveUpgrade();
	
	const int Index = CharacterUpgrades.Find(Upgrade);
	if (Index == INDEX_NONE)
	{
		UE_LOG(LogCharacterUpgradeComponent, Warning, TEXT("Upgrade not found in CharacterUpgrades array"));
		return nullptr;
	}
	
	CharacterUpgrades[Index] = nullptr;
	return Upgrade;
}

bool UCharacterUpgradesComponent::AddToUpgradesArray(UCharacterUpgrade* UpgradeToAdd, int32& SlotIndex)
{
	
	for (int i = 0; i < CharacterUpgrades.Num(); ++i)
	{
		if (CharacterUpgrades[i] == nullptr)
		{
			CharacterUpgrades[i] = UpgradeToAdd; // Add the new upgrade to the first available slot
			SlotIndex = i; // Output the index of the slot where the upgrade was added
			OnUpgradeChanged.Broadcast(UpgradeToAdd, SlotIndex);// Broadcast the upgrade change event
			CharacterUpgrades[i]->OnGrantUpgrade();
			return true; // Successfully added the upgrade to the character
		}
	}
	
	UE_LOG(LogCharacterUpgradeComponent, Error, 
		TEXT("No available slot to add the upgrade || No resized array for character upgrades"));
	return false;
}

