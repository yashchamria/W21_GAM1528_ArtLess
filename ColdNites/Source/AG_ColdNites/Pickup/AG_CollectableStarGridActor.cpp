#include "AG_CollectableStarGridActor.h"
#include "AG_ColdNites/EventManager/AG_EventManager.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"

AAG_CollectableStarGridActor::AAG_CollectableStarGridActor()
{
	
}

void AAG_CollectableStarGridActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + ActorHeight));

}

void AAG_CollectableStarGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FloatingEffect(DeltaTime);

	if (CheckPlayerOnTheTile())
	{
		if(PlayerCharacter->bIsReached)
		{
			OnCollected();
		}
	}
}

void AAG_CollectableStarGridActor::OnCollected()
{
	EventManager->UpdateStarCount();

	Destroy();
}

void AAG_CollectableStarGridActor::FloatingEffect(float delta)
{
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + delta) - FMath::Sin(RunningTime));
	NewLocation.Z += (DeltaHeight * MoveOnZ);

	//Increment RunningTime
	RunningTime += delta * floatSpeed;
	SetActorLocation(NewLocation);

	FRotator NewRotation = GetActorRotation();
	angle += delta * RotateSpeed;
	NewRotation.Yaw = angle;
	SetActorRotation(NewRotation);
}
