// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterUpgradesComponent.h"

#include "Logs/ProjectLogs.h"
#include "RunetimeItems/CharacterUpgrade.h"

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

	// ...
	
}


// Called every frame
void UCharacterUpgradesComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UCharacterUpgradesComponent::IsEnoughDataToApplyUpgrade(UCharacterUpgrade* Upgrade, float& MissingData) const
{
	if (!Upgrade)
	{
		UE_LOG(LogCharacterUpgradeInventory, Warning, TEXT("Invalid Upgrade provided to IsEnoughDataToApplyUpgrade"));
		return false;
	}
	
	float DataToActiveUpgrade = Upgrade->DataToActiveUpgrade;
	float FinalDataToApply = CharacterData + Upgrade->DataToActiveUpgrade;
	
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
		UE_LOG(LogCharacterUpgradeInventory, Error, TEXT("Invalid Upgrade Class"));
		return nullptr;
	}
	
	UCharacterUpgrade* NewUpgrade = NewObject<UCharacterUpgrade>(this, UpgradeClass);
	//NewUpgrade->InitializeUpgrade();
	
	
	CharacterUpgrades.Add(NewUpgrade);
	return NewUpgrade;
}

bool UCharacterUpgradesComponent::ApplyUpgrade(TSubclassOf<UCharacterUpgrade> Upgrade, uint8& OutIndex)
{
	if (!Upgrade)
	{
		UE_LOG(LogCharacterUpgradeInventory, Warning, TEXT("Invalid Upgrade provided to ApplyUpgrade"));
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

bool UCharacterUpgradesComponent::RemoveUpgrade(UCharacterUpgrade* Upgrade)
{
	if (!Upgrade)
	{
		UE_LOG(LogCharacterUpgradeInventory, Warning, TEXT("Invalid Upgrade provided to RemoveUpgrade"));
		return false;
	}
	
	UnlockUsedCharacterData(Upgrade->DataToActiveUpgrade);
	CharacterUpgrades.Remove(Upgrade);
	return false;
}

bool UCharacterUpgradesComponent::AddToUpgradesArray(UCharacterUpgrade* UpgradeToAdd, uint8& SlotIndex)
{
	
	for (int i = 0; i < CharacterUpgrades.Num(); ++i)
	{
		if (!CharacterUpgrades[i])
		{
			CharacterUpgrades[i] = UpgradeToAdd; // Add the new upgrade to the first available slot
			SlotIndex = i; // Output the index of the slot where the upgrade was added
			CharacterUpgrades[i]->OnGrantUpgrade(this);
			return true; // Successfully added the upgrade to the character
		}
	}
	
	UE_LOG(LogCharacterUpgradeInventory, Error, 
		TEXT("No available slot to add the upgrade || No resized array for character upgrades"));
	return false;
}

