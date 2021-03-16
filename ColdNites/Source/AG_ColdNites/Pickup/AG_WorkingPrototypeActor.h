#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_BaseGridActor.h"
#include "AG_WorkingPrototypeActor.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_WorkingPrototypeActor : public AAG_BaseGridActor
{
	GENERATED_BODY()

public:
	AAG_WorkingPrototypeActor();

protected:
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool bTriggerCollection = false;
	bool bCollected = false;
	float CollectDelay = 1.65;
};
