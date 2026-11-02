// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventoryLibrary.generated.h"

struct FWeaponRuntimeData;
/**
 * 
 */
UCLASS()
class PROJECT_R04B_API UInventoryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="InventoryLibrary")
	static int32 GetWeaponUpgradesSize(const FWeaponRuntimeData& WeaponRuntimeData);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="InventoryLibrary")
	static FColor GetUpgradeColorByRarity(ERarity Rarity);
};
