#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_AIBaseGridCharacter.h"
#include "AG_AITurnManager.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_AITurnManager : public AAG_AIBaseGridCharacter
{
	GENERATED_BODY()

public:
	AAG_AITurnManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "AG_AITurnSystem")
	float AITurnTimer;

};
