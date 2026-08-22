// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Characters/PlayableCharacters/BasePlayerChracter.h"


// Sets default values
ABasePlayerChracter::ABasePlayerChracter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void ABasePlayerChracter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayerChracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePlayerChracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

