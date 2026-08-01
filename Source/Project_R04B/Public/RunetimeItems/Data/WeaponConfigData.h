#pragma once

#include "CoreMinimal.h"
#include "Textures/TextureAtlas.h"
#include "Rarity.h"
#include "FireTypes.h"
#include "WeaponFireTypes.h"
#include "WeaponConfigData.generated.h"

class UWeaponObject;

USTRUCT(BlueprintType)
struct FWeaponConfigData
{
	GENERATED_BODY()
	
public:
	
	FWeaponConfigData();
	
	//---------------------- Weapon Class ---------------------//
	
	// Class of the weapon object to spawn, can be used to determine the type of weapon and its behavior in the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config")
	TSubclassOf<UWeaponObject> WeaponClass;
	
	//--------------------- Weapon Info ---------------------//
	
	// Name of the weapon, can be displayed in UI and used for identification
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Info")
	FName Name;
	
	// Description of the weapon, can be displayed in UI to provide flavor text and details about the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Info")
	FText Description;
	
	// Icon for the weapon, can be displayed in UI to visually represent the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Info")
	TObjectPtr<UTexture2D> Icon;
	
	//--------------------- Weapon Stats ---------------------//
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config")
	int32 BaseMaxAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config")
	int32 BaseClipSize;
	
	//---------------------- Weapon Combat Stats ---------------------//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Combat")
	float BaseFireRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Combat")
	float BaseReloadTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Combat")
	EFireType BaseFireType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Combat")
	ERarity Rarity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Config | Combat")
	EWeaponFireTypes WeaponFireType;

};

inline FWeaponConfigData::FWeaponConfigData()
{
	WeaponClass = nullptr;
	Name = FName("Default Weapon");
	Description = FText::FromString("This is a default weapon description. Replace this with specific Text");
	Icon = nullptr;
	BaseMaxAmmo = 30;
	BaseClipSize = 10;
	BaseFireRate = 0.5f;
	BaseReloadTime = 2.0f;
	BaseFireType = EFireType::SingleFire;
	Rarity = ERarity::Common;
	WeaponFireType = EWeaponFireTypes::Projectile;
}

