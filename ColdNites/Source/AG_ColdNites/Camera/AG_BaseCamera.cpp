#include "AG_BaseCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAG_BaseCamera::AAG_BaseCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Default Camera Arm"));
	DefaultCameraArm->SetUsingAbsoluteRotation(true);
	DefaultCameraArm->TargetArmLength = 900.f;
	DefaultCameraArm->bDoCollisionTest = false;

	DefaultCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Default Camera"));
	DefaultCamera->SetupAttachment(DefaultCameraArm, USpringArmComponent::SocketName);
	DefaultCamera->bUsePawnControlRotation = false;
	
	DefaultCamera->bConstrainAspectRatio = true;
	DefaultCamera->SetFieldOfView(90.0f);

	DefaultCamera->PostProcessSettings.AutoExposureMinBrightness = 1.2f;
	DefaultCamera->PostProcessSettings.AutoExposureMaxBrightness = 1.2f;
	
	Tags.Add("Camera00");
}

void AAG_BaseCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_BaseCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

