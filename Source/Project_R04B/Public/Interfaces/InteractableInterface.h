#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintInternalUseOnly)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};
class PROJECT_R04B_API IInteractableInterface
{
	GENERATED_BODY()
		
public:
		
		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
		void Interact(AActor* InteractingActor);
};
