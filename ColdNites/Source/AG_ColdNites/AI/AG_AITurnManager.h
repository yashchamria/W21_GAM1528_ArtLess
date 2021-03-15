#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_AITurnManager.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_AITurnManager : public AActor
{
	GENERATED_BODY()

public:
	AAG_AITurnManager();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	class AAG_ColdNitesGameModeBase* GameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_AIIInfo")
		TArray<class AAG_AIBaseGridCharacter*> AllPresentAIActors;

	void RegisterToAIManager(AAG_AIBaseGridCharacter* AIActor);
	void UnRegisterToAIManager(AAG_AIBaseGridCharacter* AIActor);

	bool CheckIsAITurn();
	void ResetAfterAITurn();

private:
	float PlayerRestTimer = 3.25f;
};
