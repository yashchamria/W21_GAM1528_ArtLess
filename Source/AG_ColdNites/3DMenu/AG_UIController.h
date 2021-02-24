#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AG_UIController.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_UIController : public APlayerController
{
	GENERATED_BODY()

public:
	AAG_UIController();

	TArray<AActor*> Buttons;
	float YawVals[3];
	
	bool bNextClicked;
	bool bPrevClicked;

	float RotationRate;

	FRotator InitRot;

	int in;
	float ip;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void OnNextClicked();

	UFUNCTION(BlueprintCallable)
	void OnPrevClicked();

	void RotateOnNextClicked(float val);
	void RotateOnPrevClicked(float val);
};
