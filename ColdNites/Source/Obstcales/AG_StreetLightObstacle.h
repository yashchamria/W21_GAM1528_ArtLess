// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_BaseGridActor.h"
#include "AG_StreetLightObstacle.generated.h"

/**
 * 
 */
UCLASS()
class AG_COLDNITES_API AAG_StreetLightObstacle : public AAG_BaseGridActor
{
	GENERATED_BODY()

public:

	void SetWalkable();
	void DisableWalable();
	void CheckTurnCounter();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	uint32 Coord;
};
