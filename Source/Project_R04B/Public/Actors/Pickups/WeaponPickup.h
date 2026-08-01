// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPickup.h"
#include "GameFramework/Actor.h"
#include "RunetimeItems/Data/WeaponRuntimeData.h"
#include "WeaponPickup.generated.h"

class UWeaponDataAsset;

UCLASS()
class PROJECT_R04B_API AWeaponPickup : public AItemPickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponPickup();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Pickup")
	TObjectPtr<UWeaponDataAsset> WeaponDataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Pickup")
	FWeaponRuntimeData WeaponRuntimeData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	

};
