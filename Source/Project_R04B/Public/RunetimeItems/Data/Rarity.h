#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	Unique UMETA(DisplayName = "Unique"),
};
