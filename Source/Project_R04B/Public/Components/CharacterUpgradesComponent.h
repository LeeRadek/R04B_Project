// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterUpgradesComponent.generated.h"

class AR04BPlayerState;
class ABasePlayerChracter;
class UCharacterUpgrade;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpgradeChanged, UCharacterUpgrade*, Upgrade, int32, UpgradeIndex);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType, Abstract)
class PROJECT_R04B_API UCharacterUpgradesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterUpgradesComponent();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Character Upgrades")
	TObjectPtr<ABasePlayerChracter> OwningPlayer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Pointer to the player state that owns this component, allowing for access to player-specific data and functionality
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<AR04BPlayerState> OwningPlayerState;

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
	bool IsEnoughDataToApplyUpgrade(TSubclassOf<UCharacterUpgrade> Upgrade, float& MissingData) const;
	
	// Function to create a new character upgrade object based on a specified upgrade class, returning success status
	UFUNCTION()
	UCharacterUpgrade* CreateCharacterUpgrade(TSubclassOf<UCharacterUpgrade> UpgradeClass);
	
	// Apply a character upgrade to the character, modifying the character's data and state based on the upgrade's effects
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	bool ApplyUpgrade(TSubclassOf<UCharacterUpgrade> Upgrade, int32& OutIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	UCharacterUpgrade* RemoveUpgrade(UCharacterUpgrade* Upgrade);
	
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades")
	void UnlockUsedCharacterData(float ValueToUnlock) { LockedCharacterData -= ValueToUnlock; }
	
	// Function to apply a character upgrade, modifying the character's data based on the upgrade's effects
	UPROPERTY(BlueprintAssignable, Category = "Character Upgrades")
	FOnDataChange OnDataChange;
	
	UPROPERTY(BlueprintAssignable, Category = "Character Upgrades")
	FOnUpgradeChanged OnUpgradeChanged;
	
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
	
	UFUNCTION()
	bool AddToUpgradesArray(UCharacterUpgrade* UpgradeToAdd, int32& UpgradeIndex);
	
	/// Resize the character upgrades array to a new size,
	/// allowing for dynamic management of the number of upgrades the character can hold
	/// @param NewSize - The new size for the character upgrades array
	UFUNCTION(BlueprintCallable, Category = "Character Upgrades", meta = (DisplayName = "Resize Character Upgrades Array"))
	void ResizeUpgradesArray(int32 NewSize) { CharacterUpgrades.SetNum(NewSize); }
	
	
	
};
