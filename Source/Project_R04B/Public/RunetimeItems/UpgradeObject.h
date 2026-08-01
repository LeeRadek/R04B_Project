// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UpgradeObject.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class PROJECT_R04B_API UUpgradeObject : public UObject
{
	GENERATED_BODY()
	
public:
	
	UUpgradeObject();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Upgrade")
	TObjectPtr<AActor> Owner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon Upgrade")
	FName UpgradeName;
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon Upgrade", DisplayName="Start Fire")
	void StartFire();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon Upgrade", DisplayName="Stop Fire")
	void StopFire();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon Upgrade", DisplayName="On Hit")
	void OnHit();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Weapon Upgrade", DisplayName="On Reload")
	void OnReload();
	
	// Initialization function to set up the upgrade with its owner and world context
	UFUNCTION()
	void Initialize(AActor* UpgradeOwner);
	
	
};
