#include "AG_CameraManager.h"
#include "AG_BaseCamera.h"
#include "AG_ColdNites/Player/AG_PlayerController.h"
#include "AG_ColdNites/3DMenu/AG_UIController.h"
#include "AG_ColdNites/EventManager/AG_EventManager.h"
#include "Kismet/GameplayStatics.h"

AAG_CameraManager::AAG_CameraManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bLockLocation = true;

	Tags.Add("CameraManager");
}

void AAG_CameraManager::BeginPlay()
{
	Super::BeginPlay();

	//Getting PlayerController
	APlayerController* CurrentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (CurrentController) { PlayerController = Cast<AAG_PlayerController>(CurrentController); }
	if (CurrentController) { UIController = Cast<AAG_UIController>(CurrentController); }

	//Getting EventManager
	TArray<AActor*> EventManagerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_EventManager::StaticClass(), EventManagerActor);
	if (EventManagerActor.Num() > 0) { EventManager = Cast<AAG_EventManager>(EventManagerActor[0]); }
	
	CurrentCameraActorTag = "Camera00";
	SwitchCamera(CurrentCameraActorTag, 0);
}

void AAG_CameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EventManager)
	{
		if (CurrentCameraActorTag != EventManager->GetSwitchCameraTag())
		{
			CurrentCameraActorTag = EventManager->GetSwitchCameraTag();
			SwitchCamera(CurrentCameraActorTag, CameraBlendTime);
		}
	}
}

void AAG_CameraManager::AddCamera()
{
	FActorSpawnParameters CameraParams;
	AAG_BaseCamera* SpawnedCamera = GetWorld()->SpawnActor<AAG_BaseCamera>(FVector::ZeroVector, FRotator::ZeroRotator, CameraParams);

	FAttachmentTransformRules TileTransformRules(EAttachmentRule::KeepWorld, true);
	SpawnedCamera->AttachToActor(this, TileTransformRules);

	Cameras.Add(SpawnedCamera);
}

void AAG_CameraManager::ClearAllCameras()
{
	for (int i = 0; i < Cameras.Num(); i++)
	{
		Cameras[i]->Destroy();
	}
	Cameras.Empty();
}

void AAG_CameraManager::SwitchCamera(FName CameraActorTag, float blendTime)
{
	for (AAG_BaseCamera* CameraActor : Cameras)
	{
		if (CameraActor->ActorHasTag(CameraActorTag))
		{
			if (PlayerController)
			{
				PlayerController->SetViewTargetWithBlend(CameraActor, blendTime);
			}
			
			if(UIController)
			{
				UIController->SetViewTargetWithBlend(CameraActor, blendTime);
			}
		}
	}
}
