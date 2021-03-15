#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_AIBaseGridCharacter.h"
#include "AG_PatrollingAICharacter.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_PatrollingAICharacter : public AAG_AIBaseGridCharacter
{
	GENERATED_BODY()

public:
	AAG_PatrollingAICharacter();
	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_PatrolProperty")
		TArray<FIntPoint> PatrolTileCoords;

private:
	uint8 PatrolIndex = 0;
	FIntPoint CurrentPatrolTileCoord;

	void MoveToNextPatrolTile();
};