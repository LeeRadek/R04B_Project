#pragma once

#include "Rarity.h"
#include "RunetimeItems/UpgradeObject.h"
#include "FireTypes.h"
#include "WeaponFireTypes.h"
#include "WeaponRuntimeData.generated.h"



USTRUCT(BlueprintType)
struct FWeaponRuntimeData
{
	GENERATED_BODY()
	
public:
	
	FWeaponRuntimeData();
	
	//--------------------- Weapon Amoo Data ---------------------//
	
	// Current ammo count for the weapon, can be modified by upgrades and runtime events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Ammo")
	int32 AmmoCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Ammo")
	int32 CurrentClipSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Ammo")
	int32 MaxAmmo;
	
	//--------------------- Weapon Combat Data ---------------------//
	
	// Current fire rate of the weapon, can be modified by upgrades and runtime events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Combat")
	float FireRate;
	
	// Current reload time of the weapon, can be modified by upgrades and runtime events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Combat")
	float ReloadTime;
	
	// Current damage of the weapon, can be modified by upgrades and runtime events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Combat")
	float Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Combat")
	float ProjectileSpeed;
	
	// Current fire type of the weapon, can be modified by upgrades and runtime events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Combat")
	EFireType FireType = EFireType::SingleFire;
	
	//---------------------- Weapon Info ---------------------//
	
	// Rarity of the weapon, can be modified by upgrades and runtime events
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Info")
	ERarity Rarity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Info")
	EWeaponFireTypes WeaponFireType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data | Info")
	TArray<UUpgradeObject*> WeaponUpgrades;
	
	// Function to resize the upgrade array based on the current rarity of the weapon
	void ResizeUpgradeArray();
};

inline FWeaponRuntimeData::FWeaponRuntimeData()
{
	Rarity = ERarity::Common;
	AmmoCount = 0;
	CurrentClipSize = 0;
	MaxAmmo = 0;
	FireRate = 0.f;
	ReloadTime = 0.f;
	Damage = 0.f;
	ProjectileSpeed = 0.f;
	FireType = EFireType::SingleFire;
	WeaponFireType = EWeaponFireTypes::Projectile;
}

inline void FWeaponRuntimeData::ResizeUpgradeArray()
{
	switch (Rarity){
	case ERarity::Common:
		WeaponUpgrades.SetNum(1);
		break;
	case ERarity::Rare:
		WeaponUpgrades.SetNum(2);
		break;
	case ERarity::Epic:
		WeaponUpgrades.SetNum(3);
		break;
	case ERarity::Legendary:
		WeaponUpgrades.SetNum(4);
		break;
	case ERarity::Unique:
		WeaponUpgrades.SetNum(5);
		break;
	default:
		WeaponUpgrades.SetNum(1);
		break;
	}
}