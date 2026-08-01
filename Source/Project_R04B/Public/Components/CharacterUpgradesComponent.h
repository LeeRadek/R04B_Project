// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterUpgradesComponent.generated.h"

class UCharacterUpgrade;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataChange);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class PROJECT_R04B_API UCharacterUpgradesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterUpgradesComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	// Function to retrieve the current character data, allowing for read-only access to the character's upgrade state
	UFUNCTION( BlueprintCallable, BlueprintPure = true, Category="Character Upgrades")
	float GetCharacterData() const { return CharacterData; }
	
	// Function to add a specified value to the character's data, allowing for upgrades or modifications
	UFUNCTION( BlueprintCallable, Category = "Character Upgrades")
	void AddCharacterData(float ValueToAdd) { CharacterData += ValueToAdd; }
	
	//Check if the character has enough data to apply a specific upgrade, returning the missing data if not enough
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	bool IsEnoughDataToApplyUpgrade(UCharacterUpgrade* Upgrade, float& MissingData) const;
	
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	bool CreateCharacterUpgrade(TSubclassOf<UCharacterUpgrade> UpgradeClass);
	
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	bool ApplyUpgrade(UCharacterUpgrade* Upgrade);
	
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	bool RemoveUpgrade(UCharacterUpgrade* Upgrade);
	
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	void UnlockUsedCharacterData(float ValueToUnlock) { LockedCharacterData -= ValueToUnlock; }
	
	// Function to apply a character upgrade, modifying the character's data based on the upgrade's effects
	UPROPERTY(BlueprintAssignable, Category = "Character Upgrades")
	FOnDataChange OnDataChange;
	
private:
	
	// Variable to hold the character's data, which can be modified by upgrades and other gameplay events
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Upgrades", meta=(AllowPrivateAccess="true"))
	float CharacterData = 0.0f;
	
	// Variable to hold the character's locked data, show how much data is locked by upgrades,
	// can be used to determine if an upgrade can be applied or not
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Upgrades", meta=(AllowPrivateAccess="true"))
	float LockedCharacterData = 0.0f;
	
	// Array to hold the character's upgrades, allowing for dynamic management of upgrades and their effects on the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Upgrades", meta=(AllowPrivateAccess="true"))
	TArray<TObjectPtr<UCharacterUpgrade>> CharacterUpgrades;
	
	
};
