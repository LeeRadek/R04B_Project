// Fill out your copyright notice in the Description page of Project Settings.

#include "RunetimeItems/WeaponObject.h"
#include "UObject/UnrealType.h"

UWeaponObject::UWeaponObject()
{
	
}

void UWeaponObject::Fire_Implementation()
{
}



void UWeaponObject::StopFire_Implementation()
{
	
}
#if WITH_EDITOR



void UWeaponObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	// Resize the upgrade array in WeaponRuntimeData when the Rarity property is changed in the editor
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FWeaponRuntimeData, Rarity))
	{
		WeaponRuntimeData.ResizeUpgradeArray();
	}
}
#endif






