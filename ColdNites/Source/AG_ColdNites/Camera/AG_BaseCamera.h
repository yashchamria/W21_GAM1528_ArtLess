/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Yash Chamria

 Module:  CameraManager

 Description - The Base Camera Actor is a basic camera that has a spring arm attached to it.
			   It comes with some of the camera properties and values predefined in the code which allows a consistent look throughout the game and ease of camera creation.
******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_BaseCamera.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_BaseCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	AAG_BaseCamera();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_CameraComponent")
		class UCameraComponent* DefaultCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AG_CameraComponent")
		class USpringArmComponent* DefaultCameraArm;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
