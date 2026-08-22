// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/R04BPlayerState.h"

#include "Actors/Characters/PlayableCharacters/BasePlayerChracter.h"
#include "Components/InventoryComponent.h"
#include "Components/CharacterUpgradesComponent.h"


AR04BPlayerState::AR04BPlayerState()
{

}

UInventoryComponent* AR04BPlayerState::GetInventoryComponents() const
{
	UInventoryComponent* Component = FindComponentByClass<UInventoryComponent>();
	ensureMsgf(Component, TEXT("InventoryComponent not found on PlayerState"));// Cehck if component is valid
	return Component;
}

UCharacterUpgradesComponent* AR04BPlayerState::GetCharacterUpgradesComponents() const
{
	UCharacterUpgradesComponent* Component = FindComponentByClass<UCharacterUpgradesComponent>();
	ensureMsgf(Component, TEXT("CharacterUpgradesComponent not found on PlayerState"));
	return Component;
}

ABasePlayerChracter* AR04BPlayerState::GetCharacter() const
{
	return Cast<ABasePlayerChracter>(GetPawn());
}




