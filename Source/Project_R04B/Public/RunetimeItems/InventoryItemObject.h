// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(blueprintType)
enum class EInventoryItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	WeaponUpgrade UMETA(DisplayName = "Weapon Upgrade"),
	CharacterUpgrade UMETA(DisplayName = "Character Upgrade")
};
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryItemObject.generated.h"

/**
 * Base class for inventory items in the game.
 * This class serves as a foundation for creating various types of inventory items,
 * such as weapons, weapon upgrades, chracterupgrades.
 * It can be extended to include specific properties and behaviors for different item types.
 */
UCLASS(BlueprintType)
class PROJECT_R04B_API UInventoryItemObject : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory Item Object")
	EInventoryItemType ItemType;
	
	
};
