// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Textures/TextureAtlas.h"
#include "WeaponConfigData.h"
#include "WeaponDataAsset.generated.h"



/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_R04B_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Data")
	FWeaponConfigData WeaponConfig;
	

	
	
};


