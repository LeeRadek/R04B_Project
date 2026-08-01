// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "RunetimeItems/Data/WeaponDataAsset.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Weapons.SetNum(3); // Initialize size for 3 weapons, can be modified later to allow for dynamic inventory sizes
	// @TODO : Chamge it later to fit the design of the inventory system, this is just a placeholder for testing purposes
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventoryComponent::InitializeWeapon(UWeaponObject* WeaponToInitialize, UWeaponDataAsset* WeaponDataAsset,
	FWeaponRuntimeData WeaponRuntimeData)
{
	if (!WeaponToInitialize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid WeaponObject provided to InitailizeWeapon"));
		return;
	}
	
	if (!WeaponDataAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid WeaponDataAsset provided to InitailizeWeapon"));
		return;
	}
	
	
	WeaponToInitialize->WeaponStaticData = WeaponDataAsset;
	
	WeaponToInitialize->WeaponRuntimeData.AmmoCount = WeaponRuntimeData.AmmoCount;
	WeaponToInitialize->WeaponRuntimeData.CurrentClipSize = WeaponRuntimeData.CurrentClipSize;
	WeaponToInitialize->WeaponRuntimeData.MaxAmmo = WeaponRuntimeData.MaxAmmo;
	WeaponToInitialize->WeaponRuntimeData.FireRate = WeaponRuntimeData.FireRate;
	WeaponToInitialize->WeaponRuntimeData.ReloadTime = WeaponRuntimeData.ReloadTime;
	WeaponToInitialize->WeaponRuntimeData.Damage = WeaponRuntimeData.Damage;
	WeaponToInitialize->WeaponRuntimeData.ProjectileSpeed = WeaponRuntimeData.ProjectileSpeed;
	WeaponToInitialize->WeaponRuntimeData.FireType = WeaponRuntimeData.FireType;
	WeaponToInitialize->WeaponRuntimeData.Rarity = WeaponRuntimeData.Rarity;
	WeaponToInitialize->WeaponRuntimeData.WeaponFireType = WeaponRuntimeData.WeaponFireType;
	
	// Resize the upgrade array based on the weapon's rarity,
	// ensuring that the weapon can hold the appropriate number of upgrades for its rarity level
	WeaponToInitialize->WeaponRuntimeData.ResizeUpgradeArray();
	
	
}

UWeaponObject* UInventoryComponent::CreateWeaponObject(UWeaponDataAsset* WeaponDataAsset, FWeaponRuntimeData WeaponRuntimeData)
{
	if (!WeaponDataAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid WeaponDataAsset provided to CreateWeaponObject"));
		return nullptr;
	}
\
	AActor* OwnerActor = GetOwner();
	// Create a new weapon object
	UWeaponObject* NewWeaponObject = NewObject<UWeaponObject>(OwnerActor, WeaponDataAsset->WeaponConfig.WeaponClass);
	NewWeaponObject->Owner = OwnerActor;
	NewWeaponObject->World = GetWorld();
	
	// Initialize the new weapon object with data
	InitializeWeapon(NewWeaponObject, WeaponDataAsset, WeaponRuntimeData);
	
	return NewWeaponObject;
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Find not equiped weapon and equip it
bool UInventoryComponent::AddWeaponToInventory(UWeaponObject* NewWeapon, int32& SlotIndex)
{
	for (int32 i = 0; i < Weapons.Num(); ++i)
	{
		if (!Weapons[i]) // Check for an empty slot in the inventory
		{
			Weapons[i] = NewWeapon; // Add the new weapon to the first available slot
			UE_LOG(LogTemp, Log, TEXT("Added weapon: %s to inventory slot: %d"), *NewWeapon->GetName(), i);
			SlotIndex = i; // Output the index of the slot where the weapon was added
			return true; // Successfully added the weapon to the inventory
		}
	}
	return false;
}

bool UInventoryComponent::EquipWeapon()
{
	if (Weapons.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapons in inventory to equip"));
		return false; // No weapons in the inventory to equip
	}
	 int32 SlotIndex = Weapons.Find(EquippedWeapon);
	
	if (Weapons.IsValidIndex(SlotIndex) && !Weapons[SlotIndex])
	{
		for (int32 i = 0; i < Weapons.Num(); ++i)
		{
			if (Weapons[i])
			{
				EquippedWeapon = Weapons[i]; // Equip the first available weapon in the inventory
				UE_LOG(LogTemp, Log, TEXT("Equipped weapon: %s from inventory slot: %d"), *EquippedWeapon->GetName(), i);
				return true; // Successfully equipped a weapon
			}
		}
		
		UE_LOG(LogTemp, Warning, TEXT("No valid weapons found in inventory to equip"));
		return false;
	}
	
	for (int32 Offset = 1; Offset < Weapons.Num(); ++Offset)
	{
		int32 NextIndex = (SlotIndex + Offset) % Weapons.Num();
		if (Weapons[NextIndex])
		{
			EquippedWeapon = Weapons[NextIndex]; // Equip the next available weapon in the inventory
			UE_LOG(LogTemp, Log, TEXT("Equipped weapon: %s from inventory slot: %d"), *EquippedWeapon->GetName(), NextIndex);
			return true;
		}
	}
	
	return false; // No valid weapons found in the inventory to equip
}

bool UInventoryComponent::AddUpgradeToWeapon(UUpgradeObject* UpgradeToAdd)
{
	auto& Upgrades = EquippedWeapon->WeaponRuntimeData.WeaponUpgrades;
	for (int32 i = 0; i < Upgrades.Num(); ++i)
	{
		if (!Upgrades[i]) // Check for an empty upgrade slot in the equipped weapon
		{
			Upgrades[i] = UpgradeToAdd; // Add the new upgrade to the first available slot
			//UpgradeSlotIndex = i; // Output the index of the slot where the upgrade was added
			return true; // Successfully added the upgrade to the weapon
		}
	}

	return false;
}

UUpgradeObject* UInventoryComponent::CreateUpgradeObject(TSubclassOf<UUpgradeObject> UpgradeClass)
{
	
	if (!UpgradeClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid UpgradeClass provided to CreateUpgradeObject"));
		return nullptr;
	}
	
	AActor* OwnerActor = GetOwner();
	
	UUpgradeObject* NewUpgradeObject = NewObject<UUpgradeObject>(OwnerActor, UpgradeClass);
	return NewUpgradeObject; 
}

bool UInventoryComponent::PickupWeapon(UWeaponDataAsset* WeaponDataAsset, FWeaponRuntimeData WeaponRuntimeData)
{
	for (int32 i = 0; i < Weapons.Num(); ++i)
	{
		if (!Weapons[i])
		{
			TSubclassOf<UWeaponObject> WeaponClass = WeaponDataAsset->WeaponConfig.WeaponClass;
			
			UWeaponObject* NewWeapon = NewObject<UWeaponObject>(GetOwner(), WeaponClass);
			InitializeWeapon(NewWeapon, WeaponDataAsset, WeaponRuntimeData);
			Weapons[i] = NewWeapon; // Add the new weapon to the first available slot
			return true;
		}
	}
	
	return false;
}

bool UInventoryComponent::PickupUpgrade(TSubclassOf<UUpgradeObject> UpgradeClass)
{
	if (EquippedWeapon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon equipped to add the upgrade to"));
		return false; // No weapon equipped to add the upgrade to it
	}
	
	UUpgradeObject* Upgrade =  CreateUpgradeObject(UpgradeClass);
	AddUpgradeToWeapon(Upgrade);
	
	return true;
}

void UInventoryComponent::DropWeapon(UWeaponObject* WeaponToDrop)
{
	
}

void UInventoryComponent::DropUpgrade(UUpgradeObject* UpgradeToDrop)
{
	
}



