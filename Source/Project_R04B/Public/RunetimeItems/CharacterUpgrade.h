// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemObject.h"
#include "UObject/Object.h"
#include "CharacterUpgrade.generated.h"

class ABasePlayerChracter;
class AR04BPlayerState;
class UInventoryComponent;
class UCharacterUpgradesComponent;

class UCharacterUpgradesComponent;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class PROJECT_R04B_API UCharacterUpgrade : public UInventoryItemObject
{
	GENERATED_BODY()
	
public:
	
	UCharacterUpgrade();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Character Upgrade")
	TObjectPtr<UCharacterUpgradesComponent> OwningComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Character Upgrade")
	TObjectPtr<UInventoryComponent> WeaponInventoryComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Character Upgrade", meta=(DisplayName="Owning Player"))
	TObjectPtr<ABasePlayerChracter> OwningPlayer;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Player State")
	TObjectPtr<AR04BPlayerState> PlayerState;
	
	// Variable to hold the amount of character data required to activate this upgrade
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Upgrade")
	float DataToActiveUpgrade = 0.0f;
	
	// Function to initialize the upgrade, can be overridden in Blueprints to set up specific upgrade behavior
	UFUNCTION(BlueprintCallable, Category="Character Upgrade")
	void InitializeUpgrade(
		ABasePlayerChracter* OwningCharacter,
		UCharacterUpgradesComponent* CharacterUpgradesComponent,
		UInventoryComponent* WeaponComponent,
		AR04BPlayerState* State);
	
	// Function to handle the granting of the upgrade, allowing for modifications to the character's data and state
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Character Upgrade")
	void OnGrantUpgrade();
	
	// Function to handle the removal of the upgrade
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Character Upgrade")
	void OnRemoveUpgrade();
};
