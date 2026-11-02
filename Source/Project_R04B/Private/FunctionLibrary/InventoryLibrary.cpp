// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/InventoryLibrary.h"
#include "RunetimeItems/Data/WeaponRuntimeData.h"

int32 UInventoryLibrary::GetWeaponUpgradesSize(const FWeaponRuntimeData& WeaponRuntimeData)
{
	return WeaponRuntimeData.WeaponUpgrades.Num();
}

FColor UInventoryLibrary::GetUpgradeColorByRarity(ERarity Rarity)
{
	switch (Rarity)
	{
	case ERarity::Common:
		return FColor::White;
	case ERarity::Rare:
		return FColor::Blue;
	case ERarity::Epic:
		return FColor::Purple;
	case ERarity::Legendary:
		return FColor::Orange;
	case ERarity::Unique:
		return FColor::Yellow;
	default:
		return FColor::Black; // Default color for undefined rarity
	}
}
