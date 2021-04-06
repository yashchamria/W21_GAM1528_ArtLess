/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module -  Camera Manager

 Description - Camera Manager is responsible for handling the game view.
			   It provides the functionality of spawning the camera and handles the switching between the desired cameras.
******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_CameraManager.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_CameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAG_CameraManager();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor, Category = "AG_CameraSetting")
		void AddCamera();

	UFUNCTION(CallInEditor, Category = "AG_CameraSetting")
		void ClearAllCameras();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_CameraSetting")
		TArray<class AAG_BaseCamera*> Cameras;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_CameraSetting")
	float CameraBlendTime = 1.0f;

	
private:
	FName CurrentCameraActorTag;
	
	class AAG_EventManager* EventManager;
	class AAG_PlayerController* PlayerController;
	class AAG_UIController* UIController;
	
	void SwitchCamera(FName CameraActorTag, float blendTime = 1.0f);
};
