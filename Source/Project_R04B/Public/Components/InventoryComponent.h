// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RunetimeItems/WeaponObject.h"
#include "InventoryComponent.generated.h"


class UWeaponObject;
class UWeaponDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponEquipped, UWeaponObject*, EquippedWeapon, int32, SlotIndex);

// Component to manage the player's inventory of weapons, allowing for adding, equipping, and upgrading weapons
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnable), Blueprintable, BlueprintType, Abstract)
class PROJECT_R04B_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	// Array to hold the player's weapons in the inventory
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="InventoryComponent")
	TArray<TObjectPtr<UWeaponObject>> Weapons;
	
	// Pointer to the currently equipped weapon, can be nullptr if no weapon is equipped
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="InventoryComponent")
	TObjectPtr<UWeaponObject> EquippedWeapon;
	
	// Delegate to notify when a weapon is equipped, allowing for UI updates and other gameplay logic
	UPROPERTY(BlueprintAssignable, Category="InventoryComponent")
	FOnWeaponEquipped OnWeaponEquipped;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Function to initialize a weapon object with its static and runtime data
	// @param WeaponToInitialize - The weapon object to initialize with data
	// @param WeaponDataAsset - The data asset containing the configuration and static data for the
	UFUNCTION()
	static void InitializeWeapon(UWeaponObject* WeaponToInitialize, UWeaponDataAsset* WeaponDataAsset,
		FWeaponRuntimeData WeaponRuntimeData);

	// Function to create a new weapon object based on a weapon data asset
	// @param WeaponDataAsset - The data asset containing the configuration and static data for the weapon to create
	// @return A pointer to the newly created weapon object, or nullptr if the creation failed
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	UWeaponObject* CreateWeaponObject(UWeaponDataAsset* WeaponDataAsset, FWeaponRuntimeData WeaponRuntimeData);
	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Function to add a weapon to the inventory, returns true if the weapon was successfully added
	// @param NewWeapon - The weapon object to add to the inventory
	// @param SlotIndex - Output parameter that will contain the index of the inventory slot where the weapon was added
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	bool AddWeaponToInventory(UWeaponObject* NewWeapon, int32& SlotIndex);
	
	// Function to equip a weapon from the inventory, returns true if the weapon was successfully equipped
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	bool EquipWeapon();
	
	// Function to add an upgrade to the currently equipped weapon,
	// returns true if the upgrade was successfully added and outputs the index of the upgrade slot where it was added
	// @param UpgradeToAdd - The upgrade object to add to the equipped weapon
	UFUNCTION(BlueprintCallable, Category="InventoryComponent", DisplayName="Add Upgrade To Equipped Weapon")
	bool AddUpgradeToWeapon(UUpgradeObject* UpgradeToAdd);
	
	// Function to create a new upgrade object based on a specified upgrade class
	// @param UpgradeClass - The class of the upgrade object to create, must be a subclass of UUpgradeObject
	// @return A pointer to the newly created upgrade object, or nullptr if the creation failed
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	UUpgradeObject* CreateUpgradeObject(TSubclassOf<UUpgradeObject> UpgradeClass);
	
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	bool PickupWeapon(UWeaponDataAsset* WeaponDataAsset, FWeaponRuntimeData WeaponRuntimeData);
	
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	bool PickupUpgrade(TSubclassOf<UUpgradeObject> UpgradeClass);
	
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	void DropWeapon(UWeaponObject* WeaponToDrop);
	
	UFUNCTION(BlueprintCallable, Category="InventoryComponent")
	void DropUpgrade(UUpgradeObject* UpgradeToDrop);
};
