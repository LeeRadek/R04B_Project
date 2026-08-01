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

	// ...
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
		UE_LOG(LogInventory, Warning, TEXT("Invalid Upgrade provided to IsEnoughDataToApplyUpgrade"));
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

bool UCharacterUpgradesComponent::CreateCharacterUpgrade(TSubclassOf<UCharacterUpgrade> UpgradeClass)
{
	if (!UpgradeClass)
	{
		UE_LOG(LogInventory, Error, TEXT("Invalid Upgrade Class"));
		return false;
	}
	
	UCharacterUpgrade* NewUpgrade = NewObject<UCharacterUpgrade>();
	
	CharacterUpgrades.Add(NewUpgrade);
	return true;
}

bool UCharacterUpgradesComponent::ApplyUpgrade(UCharacterUpgrade* Upgrade)
{
	if (!Upgrade)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Upgrade provided to ApplyUpgrade"));
		return false;
	}
	
	//CreateCharacterUpgrade()
	
	return false;
}

bool UCharacterUpgradesComponent::RemoveUpgrade(UCharacterUpgrade* Upgrade)
{
	if (!Upgrade)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Upgrade provided to RemoveUpgrade"));
		return false;
	}
	
	UnlockUsedCharacterData(Upgrade->DataToActiveUpgrade);
	CharacterUpgrades.Remove(Upgrade);
	return false;
}

