// Fill out your copyright notice in the Description page of Project Settings.


#include "RunetimeItems/CharacterUpgrade.h"

#include "Logs/ProjectLogs.h"

void UCharacterUpgrade::InitializeUpgrade()
{
}

void UCharacterUpgrade::OnRemoveUpgrade_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("OnRemoveUpgrade called for upgrade: %s"), *GetName());
	
}

void UCharacterUpgrade::OnGrantUpgrade_Implementation(UCharacterUpgradesComponent* CharacterUpgradesComponent)
{
	UE_LOG(LogChracterUpgradeObject, Log, TEXT("OnGrantUpgrade called for upgrade: %s"), *GetName());
	OnGrantUpgrade_Implementation(CharacterUpgradesComponent);
}

