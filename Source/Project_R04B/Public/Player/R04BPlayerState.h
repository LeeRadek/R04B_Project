// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "R04BPlayerState.generated.h"

class ABasePlayerChracter;
class UInventoryComponent;
class UCharacterUpgradesComponent;
/**
 * 
 */
UCLASS()
class PROJECT_R04B_API AR04BPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	AR04BPlayerState();
	
	UFUNCTION(BlueprintCallable, Category="Player State")
	UInventoryComponent* GetInventoryComponents() const;
	
	UFUNCTION(BlueprintCallable, Category="Player State")
	UCharacterUpgradesComponent* GetCharacterUpgradesComponents() const;
	
	UFUNCTION(BlueprintCallable, Category = "Player State")
	ABasePlayerChracter* GetCharacter() const;
	

};
