// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPickup.h"
#include "WeaponUpgradePickup.generated.h"

UCLASS()
class PROJECT_R04B_API AWeaponUpgradePickup : public AItemPickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponUpgradePickup();
	
	UPROPERTY(EditAnywhere, Category="Weapon Upgrade Pickup")
	TSubclassOf<class UUpgradeObject> UpgradeClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UFUNCTION(BlueprintCallable, Category="Character Upgrade Pickup")
	virtual void Interact_Implementation(AActor* InteractingActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "Character Upgrade Pickup")
	void ApplyWeaponUpgrade(AActor* InteractingActor);
};
