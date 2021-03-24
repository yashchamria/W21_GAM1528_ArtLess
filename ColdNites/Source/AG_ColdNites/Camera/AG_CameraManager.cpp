#include "AG_CameraManager.h"
#include "AG_BaseCamera.h"
#include "AG_ColdNites/Player/AG_PlayerController.h"
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

	//Getting all the Camera actors.
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_BaseCamera::StaticClass(), CameraActors);

	if (CameraActors.Num() > 0)
	{
		for (int i = 0; i < CameraActors.Num(); i++)
		{
			Cameras.Insert(Cast<AAG_BaseCamera>(CameraActors[i]), i);
		}
	}

	//Getting PlayerController
	APlayerController* CurrentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (CurrentController) { PlayerController = Cast<AAG_PlayerController>(CurrentController); }

	//Getting EventManager
	TArray<AActor*> EventManagerActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_EventManager::StaticClass(), EventManagerActor);
	if (EventManagerActor.Num() > 0) { EventManager = Cast<AAG_EventManager>(EventManagerActor[0]); }
	
	CurrentCameraActorTag = "Camera01";
	SwitchCamera(CurrentCameraActorTag);
}

void AAG_CameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentCameraActorTag != EventManager->GetSwitchCameraTag())
	{
		CurrentCameraActorTag = EventManager->GetSwitchCameraTag();
		SwitchCamera(CurrentCameraActorTag);
	}
}

void AAG_CameraManager::SwitchCamera(FName CameraActorTag)
{
	for(AAG_BaseCamera* CameraActor : Cameras)
	{
		if(CameraActor->ActorHasTag(CameraActorTag))
		{
			PlayerController->SetViewTargetWithBlend(CameraActor, CameraBlendTime);
		}
	}
}
