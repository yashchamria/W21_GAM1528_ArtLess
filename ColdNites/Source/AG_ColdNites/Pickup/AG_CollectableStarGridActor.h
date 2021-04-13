#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_BaseGridActor.h"
#include "AG_CollectableStarGridActor.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_CollectableStarGridActor : public AAG_BaseGridActor
{
	GENERATED_BODY()
	
public:
	AAG_CollectableStarGridActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void OnCollected();

//For Floating Effect	
private:	
	void FloatingEffect(float delta);

	float ActorHeight = 10.0f;
	float RunningTime = 0.0f;
	float MoveOnZ = 2.0f;
	float floatSpeed = 5.0f;

	float angle = 0.0f;
	float RotateSpeed = 60.0f;
};
