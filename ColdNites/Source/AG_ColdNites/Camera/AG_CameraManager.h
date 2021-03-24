/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  CameraManager

 Description - WIP ---> Will be reponsible for all the camera transition throughout the level and the game.
			  
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_CameraComponent")
		TArray<class AAG_BaseCamera*> Cameras;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_CameraSetting")
	float CameraBlendTime = 1.0f;
	
private:
	FName CurrentCameraActorTag;
	
	class AAG_PlayerController* PlayerController;
	
	class AAG_EventManager* EventManager;
	
	void SwitchCamera(FName CameraActorTag);
};
