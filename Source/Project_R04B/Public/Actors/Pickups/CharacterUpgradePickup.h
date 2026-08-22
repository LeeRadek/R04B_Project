// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPickup.h"
#include "RunetimeItems/Data/CharacterUpgradeData.h"
#include "CharacterUpgradePickup.generated.h"



UCLASS()
class PROJECT_R04B_API ACharacterUpgradePickup : public AItemPickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACharacterUpgradePickup();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Upgrade Pickup")
	FCharacterUpgradeData CharacterUpgradeData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="Character Upgrade Pickup")
	virtual void Interact_Implementation(AActor* InteractingActor) override;
	
	UFUNCTION(BlueprintCallable, Category="Character Upgrade Pickup")
	void ApplyCharacterUpgrade(AActor* InteractingActor);
};
