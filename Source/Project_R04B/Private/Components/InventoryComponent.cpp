// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Actors/Characters/PlayableCharacters/BasePlayerChracter.h"
#include "GameFramework/PlayerState.h"
#include "Logs/ProjectLogs.h"
#include "RunetimeItems/Data/WeaponDataAsset.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	APlayerState* PS = Cast<APlayerState>(GetOwner());
	ACharacter* PlayerCharacter = Cast<ACharacter>(PS->GetPawn());
	ABasePlayerChracter* BasePlayerCharacter = Cast<ABasePlayerChracter>(PlayerCharacter);
	GiveStartWeapon(BasePlayerCharacter->StartWeaponData);
	// ...
	
}

void UInventoryComponent::InitializeWeapon(UWeaponObject* WeaponToInitialize, UWeaponDataAsset* WeaponDataAsset,
	const FWeaponRuntimeData& WeaponRuntimeData, bool bIsNewWeapon)
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
	
	InitializePickedUpWeapon(WeaponToInitialize, WeaponDataAsset, WeaponRuntimeData, bIsNewWeapon);
	
}

UWeaponObject* UInventoryComponent::CreateWeaponObject(UWeaponDataAsset* WeaponDataAsset, const FWeaponRuntimeData& WeaponRuntimeData)
{
	if (!WeaponDataAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid WeaponDataAsset provided to CreateWeaponObject"));
		return nullptr;
	}

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

// 
bool UInventoryComponent::AddWeaponToInventory(UWeaponObject* NewWeapon, int32& SlotIndex)
{
	if (!NewWeapon)
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT("Invalid WeaponObject provided to AddWeaponToInventory"));
		return false; // Invalid weapon object provided
	}
	
	SlotIndex = Weapons.Add(NewWeapon); // Add the new weapon to the inventory and get its slot index
	return true;
}

bool UInventoryComponent::EquipWeapon()
{
	if (Weapons.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapons in inventory to equip"));
		return false; // No weapons in the inventory to equip
	}
	 const int32 CurrentIndex = Weapons.Find(EquippedWeapon);
	
	if (CurrentIndex == INDEX_NONE)
	{
		for (int32 i = 0; i < Weapons.Num(); ++i)
		{
			if (IsValid(Weapons[i]))
			{
				EquippedWeapon = Weapons[i]; // Equip the first available weapon in the inventory
				UE_LOG(LogWeaponInventory, Log, TEXT("Equipped weapon: %s from inventory slot: %d"), *EquippedWeapon->GetName(), i);
				return true; // Successfully equipped a weapon
			}
		}
		return false;
	}
		
	for (int32 Offset = 1; Offset < Weapons.Num(); ++Offset)
	{
		const int32 NextIndex = (CurrentIndex + Offset) % Weapons.Num();
		if (IsValid(Weapons[NextIndex]))
		{
			EquippedWeapon = Weapons[NextIndex]; // Equip the next available weapon in the inventory
			UE_LOG(LogTemp, Log, TEXT("Equipped weapon: %s from inventory slot: %d"), *EquippedWeapon->GetName(), NextIndex);
			return true;
		}
		return false;
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
			OnUpgradeAddedToWeapon.Broadcast(UpgradeToAdd, i); // Broadcast Delegate for UI
			return true; // Successfully added the upgrade to the weapon
		}
	}
	
	UE_LOG(LogWeaponInventory, Warning, TEXT("No available upgrade slots in the equipped weapon to add the upgrade: %s"), *UpgradeToAdd->GetName());
	return false;
}

bool UInventoryComponent::IsAnyEmptyUpgradeSlotInEquippedWeapon() const
{
	const auto& Upgrades = EquippedWeapon->WeaponRuntimeData.WeaponUpgrades;
	for (int32 i = 0; i < Upgrades.Num(); ++i)
	{
		if (!Upgrades[i])
		{
			return true;
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

bool UInventoryComponent::PickupWeapon(UWeaponDataAsset* WeaponDataAsset, FWeaponRuntimeData WeaponRuntimeData, bool bIsNewWeapon)
{
	if (!WeaponDataAsset)
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT("Invalid WeaponDataAsset provided to PickupWeapon"));
		return false; // Invalid weapon data asset provided
	}
	UWeaponObject* NewWeapon = CreateWeaponObject(WeaponDataAsset, WeaponRuntimeData);
	InitializeWeapon(NewWeapon, WeaponDataAsset, WeaponRuntimeData, bIsNewWeapon);
			
	int32 SlotIndex;
	AddWeaponToInventory(NewWeapon, SlotIndex); // Cheki if this ok later
	OnWeaponPickedUp.Broadcast(WeaponDataAsset, NewWeapon->WeaponRuntimeData, NewWeapon); // Update UI Slot
	
	return true;
}

bool UInventoryComponent::PickupUpgrade(TSubclassOf<UUpgradeObject> UpgradeClass)
{
	if (!UpgradeClass)
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT("Invalid UpgradeClass provided to PickupUpgrade"));
		return false; // Invalid upgrade class provided
	}
	
	if (!EquippedWeapon || !IsAnyEmptyUpgradeSlotInEquippedWeapon())
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT(
			"No equipped weapon or no empty upgrade slots available to add the upgrade: %s"),
			*UpgradeClass->GetName());
		return false; // No weapon equipped to add the upgrade to it
	}
	
	UUpgradeObject* Upgrade =  CreateUpgradeObject(UpgradeClass);
	
	if (!Upgrade)
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT("Failed to create upgrade object from class: %s"), *UpgradeClass->GetName());
		return false; // Failed to create the upgrade object
	}
	
	if (!AddUpgradeToWeapon(Upgrade))
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT("Failed to add upgrade: %s to equipped weapon: %s"), *Upgrade->GetName(), *EquippedWeapon->GetName());
		return false; // Failed to add the upgrade to the equipped weapon
	}
	
	return true;
}

void UInventoryComponent::DropWeapon(UWeaponObject* WeaponToDrop)
{
	
}

void UInventoryComponent::DropUpgrade(UUpgradeObject* UpgradeToDrop)
{
	
}

UUpgradeObject* UInventoryComponent::FindUpgradeInEquipedWeapon(UUpgradeObject* UpgradeToRemove, int32& SlotIndex) const
{
	TArray<UUpgradeObject*>& Upgrades = EquippedWeapon->WeaponRuntimeData.WeaponUpgrades;
	
	for (int32 i = 0; i < Upgrades.Num(); ++i)
	{
		if (Upgrades[i] == UpgradeToRemove)
		{
			SlotIndex = i + 1;
			return Upgrades[i];
		}
	}
	
	UE_LOG(LogWeaponInventory, Error, TEXT("Not Found Weapon Upgrade In Current Equiped Weapon"));
	return nullptr;
}

void UInventoryComponent::GiveStartWeapon(UWeaponDataAsset* StartWeaponData)
{
	if (!StartWeaponData)
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT("Invalid StartWeaponData provided to GiveStartWeapon"));
		return;
	}
	UWeaponObject* NewWeapon = CreateWeaponObject(StartWeaponData, FWeaponRuntimeData());
	InitializeWeapon(NewWeapon, StartWeaponData, FWeaponRuntimeData(), true);
	int32 SlotIndex;
	AddWeaponToInventory(NewWeapon, SlotIndex);
	EquipWeapon();
}

void UInventoryComponent::InitializePickedUpWeapon(UWeaponObject* PickedUpWeapon, UWeaponDataAsset* PickedUpWeaponData,
	const FWeaponRuntimeData& PickedUpWeaponRuntimeData, bool bIsNewWeapon)
{
	if (!PickedUpWeapon || !PickedUpWeaponData)
	{
		UE_LOG(LogWeaponInventory, Warning, TEXT("Invalid WeaponObject or WeaponDataAsset provided to InitializePickedUpWeapon"));
		return;
	}
	
	if (bIsNewWeapon)
	{
		// Initialize the new weapon with the provided data
		PickedUpWeapon->WeaponStaticData = PickedUpWeaponData;
		
		PickedUpWeapon->WeaponRuntimeData.AmmoCount = PickedUpWeaponData->WeaponConfig.BaseMaxAmmo;
		PickedUpWeapon->WeaponRuntimeData.CurrentClipSize = PickedUpWeaponData->WeaponConfig.BaseClipSize;
		PickedUpWeapon->WeaponRuntimeData.MaxAmmo = PickedUpWeaponData->WeaponConfig.BaseMaxAmmo;
		PickedUpWeapon->WeaponRuntimeData.FireRate = PickedUpWeaponData->WeaponConfig.BaseFireRate;
		PickedUpWeapon->WeaponRuntimeData.ReloadTime = PickedUpWeaponData->WeaponConfig.BaseReloadTime;
		PickedUpWeapon->WeaponRuntimeData.Damage = PickedUpWeaponData->WeaponConfig.BaseDamage;
		PickedUpWeapon->WeaponRuntimeData.ProjectileSpeed = PickedUpWeaponData->WeaponConfig.BaseProjectileSpeed;
		PickedUpWeapon->WeaponRuntimeData.FireType = PickedUpWeaponData->WeaponConfig.BaseFireType;
		PickedUpWeapon->WeaponRuntimeData.Rarity = PickedUpWeaponData->WeaponConfig.Rarity;
		PickedUpWeapon->WeaponRuntimeData.WeaponFireType = PickedUpWeaponData->WeaponConfig.WeaponFireType;
		PickedUpWeapon->WeaponRuntimeData.ResizeUpgradeArray();
		
		
	}
	else
	{
		// Update the existing weapon's runtime data with the provided data
		PickedUpWeapon->WeaponRuntimeData = PickedUpWeaponRuntimeData;
		
		PickedUpWeapon->WeaponRuntimeData.ResizeUpgradeArray();
	}
}





