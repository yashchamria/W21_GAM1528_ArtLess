#include "AG_CameraManager.h"
#include "AG_BaseCamera.h"
#include "Kismet/GameplayStatics.h"

AAG_CameraManager::AAG_CameraManager()
{
	PrimaryActorTick.bCanEverTick = true;
	bLockLocation = true;
}

void AAG_CameraManager::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_BaseCamera::StaticClass(), Cameras);
	
	if (Cameras.Num() > 0)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetViewTargetWithBlend(Cameras[0], 0);
	}
}

void AAG_CameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}