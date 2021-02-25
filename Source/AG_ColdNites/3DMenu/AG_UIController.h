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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_ButtonInfo")
	TArray<class AAG_MenuButton*> MenuButton;

	UPROPERTY()
	TArray<float> YawValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Menu")
	bool bResOptionsVisible;
	
	bool bNextClicked;
	bool bPrevClicked;

	float RotationRate;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void OnNextClicked();

	UFUNCTION(BlueprintCallable)
	void OnPrevClicked();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AG_Menu")
	void HideResOptionsMenu();
	
	void UpdateNewYawValues();

	void RotateOnNextClicked(float YawValue);
	void RotateOnPrevClicked(float YawValue);

	void RotateOnClick(float val, float Rotation);

private:
	float RotationSpeed = 0.0f;
};
