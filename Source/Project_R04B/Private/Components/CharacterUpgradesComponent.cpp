// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterUpgradesComponent.h"


// Sets default values for this component's properties
UCharacterUpgradesComponent::UCharacterUpgradesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterUpgradesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterUpgradesComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UCharacterUpgradesComponent::IsEnoughDataToApplyUpgrade(UCharacterUpgrade* Upgrade) const
{
	return false;
}

bool UCharacterUpgradesComponent::ApplyUpgrade(UCharacterUpgrade* Upgrade)
{
	if (!Upgrade)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Upgrade provided to ApplyUpgrade"));
		return false;
	}
}

