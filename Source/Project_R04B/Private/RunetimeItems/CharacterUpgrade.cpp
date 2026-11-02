// Fill out your copyright notice in the Description page of Project Settings.


#include "RunetimeItems/CharacterUpgrade.h"
#include "Components/CharacterUpgradesComponent.h"
#include "Components/InventoryComponent.h"
#include "Player/R04BPlayerState.h"
#include "Actors/Characters/PlayableCharacters/BasePlayerChracter.h"
#include "Logs/ProjectLogs.h"

UCharacterUpgrade::UCharacterUpgrade()
{
	ItemType = EInventoryItemType::CharacterUpgrade;
}

void UCharacterUpgrade::InitializeUpgrade(
	ABasePlayerChracter* OwningCharacter, 
	UCharacterUpgradesComponent* CharacterUpgradesComponent,
	UInventoryComponent* WeaponComponent,
	AR04BPlayerState* State)
{
	if (!OwningCharacter)
	{
		UE_LOG(LogCharacterUpgrade, Warning, TEXT("Invalid OwningCharacter provided to InitializeUpgrade"));
		return;
	}
	OwningPlayer = OwningCharacter;
	if (!CharacterUpgradesComponent)
	{
		UE_LOG(LogCharacterUpgrade, Warning, TEXT("Invalid CharacterUpgradesComponent provided to InitializeUpgrade"));
		return;
	}
	PlayerState = State;
	if (!CharacterUpgradesComponent)
	{
		UE_LOG(LogCharacterUpgrade, Warning, TEXT("Invalid CharacterUpgradesComponent provided to InitializeUpgrade"));
		return;
	}
	OwningComponent = CharacterUpgradesComponent;
	if (!WeaponComponent)
	{
		UE_LOG(LogCharacterUpgrade, Warning, TEXT("Invalid WeaponComponent provided to InitializeUpgrade"));
		return;
	}
	WeaponInventoryComponent = WeaponComponent;
	
}


void UCharacterUpgrade::OnRemoveUpgrade_Implementation()
{
	UE_LOG(LogCharacterUpgrade, Log, TEXT("OnRemoveUpgrade called for upgrade: %s"), *GetName());
	
}

void UCharacterUpgrade::OnGrantUpgrade_Implementation()
{
	
	
}

