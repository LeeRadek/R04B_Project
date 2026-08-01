// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/WeaponRuntimeData.h"
#include "UObject/Object.h"
#include "WeaponObject.generated.h"

class UUpgradeObject;
class UWeaponDataAsset;
/**
 * WeaponObject is a UObject class that represents an instance of a weapon in the game.
 * It contains both static data (from the WeaponDataAsset) and runtime data (from the WeaponRuntimeData struct)
 * that define the weapon's properties, stats, and behavior during gameplay.
 * The class also includes functions for firing and stopping the firing of the weapon, which can be implemented in Blueprints 
 * to allow for flexible and customizable weapon behavior based on different weapon types and configurations.
 */
UCLASS(BlueprintType, Blueprintable, HideDropdown)
class PROJECT_R04B_API UWeaponObject : public UObject
{
	GENERATED_BODY()
	
public:
	
	UWeaponObject();
	
	//---------------------- Weapon Ownership ---------------------//
	
	// Owner of the weapon, typically the character or actor wielding it
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> Owner;
	
	// World context for the weapon, can be used for spawning projectiles and accessing game state
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Data")
	TObjectPtr<UWorld> World;
	
	//---------------------- Weapon Data ---------------------//
	
	// Static data for the weapon, such as base stats and properties defined in a data asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	TObjectPtr<UWeaponDataAsset> WeaponStaticData;
	
	// Runtime data for the weapon, such as current ammo count and modified stats that can change during gameplay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	FWeaponRuntimeData WeaponRuntimeData;
	
	//---------------------- Weapon Functions ---------------------//
	
	// Function to handle firing the weapon, can be implemented in Blueprints to define specific firing behavior for different weapon types
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon Events", DisplayName="Fire")
	void Fire();
	
	// Function to handle stopping the firing of the weapon, can be implemented in Blueprints to define specific behavior
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Weapon Functions")
	void StopFire();
	
#if WITH_EDITOR
	// Override the PostEditChangeProperty function to resize the upgrade array in
	// WeaponRuntimeData when the Rarity property is changed in the editor
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
#endif
	
	
};
