#pragma once

#include "FireTypes.generated.h"

UENUM(BlueprintType)
enum class EFireType : uint8
{
	SingleFire UMETA(DisplayName = "Single Fire"),
	BurstFire UMETA(DisplayName = "Burst Fire"),
	Automatic UMETA(DisplayName = "Automatic")
};
