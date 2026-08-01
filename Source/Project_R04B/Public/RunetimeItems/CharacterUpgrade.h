// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CharacterUpgradesComponent.h"
#include "UObject/Object.h"
#include "CharacterUpgrade.generated.h"

class UCharacterUpgradesComponent;
/**
 * 
 */
UCLASS()
class PROJECT_R04B_API UCharacterUpgrade : public UObject
{
	GENERATED_BODY()
	
public:
	
	// Variable to hold the amount of character data required to activate this upgrade
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Upgrade")
	float DataToActiveUpgrade = 0.0f;
	
	// Function to initialize the upgrade, can be overridden in Blueprints to set up specific upgrade behavior
	UFUNCTION(BlueprintCallable, Category="Character Upgrade")
	void InitializeUpgrade();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Character Upgrade")
	void OnGrantUpgrade(UCharacterUpgradesComponent* CharacterUpgradesComponent);
};
