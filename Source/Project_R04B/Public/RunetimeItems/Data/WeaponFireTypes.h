#pragma once

#include "WeaponFireTypes.generated.h"

UENUM(BlueprintType)
enum class EWeaponFireTypes : uint8
{
	Projectile UMETA(DisplayName="Projectile"),
	HitScan UMETA(DisplayName="HitScan"),
};
