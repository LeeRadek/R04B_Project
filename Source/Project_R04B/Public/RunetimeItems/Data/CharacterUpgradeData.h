#pragma once

#include "CoreMinimal.h"
#include "RunetimeItems/CharacterUpgrade.h"
#include "Runtime/Engine/Private/Materials/MaterialSharedPrivate.h"
#include  "CharacterUpgradeData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterUpgradeData
{
	GENERATED_BODY()
	
public:
	
	FCharacterUpgradeData()
		: UpgradeClass(nullptr)
		, Name(NAME_None)
		, Description(FText::GetEmpty())
		, Icon(nullptr)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Upgrade Data")
	TSubclassOf<UCharacterUpgrade> UpgradeClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Upgrade Data")
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Upgrade Data")
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Upgrade Data")
	TObjectPtr<UTexture2D> Icon;
	

};
