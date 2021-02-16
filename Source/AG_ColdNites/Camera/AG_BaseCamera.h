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
