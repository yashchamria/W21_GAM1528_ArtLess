#include "AG_BaseGridCharacter.h"
#include "../TileMap/AG_TileMap.h"
#include "../GameMode/AG_ColdNitesGameModeBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

AAG_BaseGridCharacter::AAG_BaseGridCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ErrorRange = 1.1f; //Don't lower it any further...movement will end up miss some update calls and will not stop
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}

void AAG_BaseGridCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GameMode = Cast<AAG_ColdNitesGameModeBase>(GetWorld()->GetAuthGameMode());
	
	//Getting the Spawned TileMap Actor from the World
	TArray<AActor*> TileMapActor;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_TileMap::StaticClass(), TileMapActor);

	if (TileMapActor.Num() > 0)
	{
		TileMap = Cast<AAG_TileMap>(TileMapActor[0]);
		TargetTileWorldLocation = TileMap->GetTileWorldPosition(TileMap->GetTileCoord(GetActorLocation()));

		FIntPoint CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());
		TileMap->Register(this, CurrentTileCoord);

		AutoRepositionToTileCenter(CurrentTileCoord);
	}
}

void AAG_BaseGridCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AAG_BaseGridCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetActorRotation(TargetRotation); Rotates the player...Can make it hard to navigate 

	if (bWalk)
	{
		TargetDistance.X = TargetTileWorldLocation.X - GetActorLocation().X;
		TargetDistance.Y = TargetTileWorldLocation.Y - GetActorLocation().Y;

		if ((TargetDistance.X > ErrorRange || TargetDistance.X < -ErrorRange) || (TargetDistance.Y > ErrorRange || TargetDistance.Y < -ErrorRange))
		{
			AddMovementInput(TargetDirection);
		}
		else
		{
			bWalk = false;
			GameMode->FinishTurn();
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("TargetDistance: %s"), *TargetDistance.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("TargetTileWorldLocation: %s"), *TargetTileWorldLocation.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("GetActorLocation: %s"), *GetActorLocation().ToString()));
}

void AAG_BaseGridCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAG_BaseGridCharacter::MoveTile(FVector DirectionVector, uint32 TileLeap)
{
	FIntPoint CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());
	FIntPoint NextTileCoord = TileMap->GetNextTileCoord(GetActorLocation(), DirectionVector, TileLeap);

	bool IsNextTileWalkable = TileMap->GetTileProperty(NextTileCoord, AG_TileProperty::IsWalkable);

	if (IsNextTileWalkable)
	{
		bWalk = true;
		TargetTileWorldLocation = TileMap->GetTileWorldPosition(NextTileCoord);
		TargetDirection = DirectionVector;

		TileMap->UnRegister(this, CurrentTileCoord);
		TileMap->Register(this, NextTileCoord);
	}
}

void AAG_BaseGridCharacter::MoveForward()
{
	bRotate = false;
	MoveTile(GetActorForwardVector());
}

void AAG_BaseGridCharacter::MoveBackward()
{
	bRotate = true;
	TargetRotation = GetActorRotation() + FRotator(0.0f, 180.0f, 0.0f);
	MoveTile(-GetActorForwardVector());
}

void AAG_BaseGridCharacter::MoveRight()
{
	bRotate = true;
	TargetRotation = GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f);
	MoveTile(GetActorRightVector());
}

void AAG_BaseGridCharacter::MoveLeft()
{
	bRotate = true;
	TargetRotation = GetActorRotation() + FRotator(0.0f, -90.0f, 0.0f);
	MoveTile(-GetActorRightVector());
}

void AAG_BaseGridCharacter::Animate()
{

}

void AAG_BaseGridCharacter::SetAnimation(AG_AnimationStates NewState)
{
	switch (NewState)
	{
	case AG_AnimationStates::Idle:
		break;

	case AG_AnimationStates::Walk:
		break;

	case AG_AnimationStates::Rotation:
		break;

	case AG_AnimationStates::PickUp:
		break;

	case AG_AnimationStates::Attack:
		break;
	}
}

void AAG_BaseGridCharacter::AutoRepositionToTileCenter(FIntPoint TileCoord)
{
	if (TileMap && TileMap->GetTileProperty(TileCoord, AG_TileProperty::IsWalkable))
	{
		FVector NewLocation = TileMap->GetTileWorldPosition(TileCoord);
		NewLocation.Z = 0.0f;
		SetActorLocation(NewLocation);

		TileMap->Register(this, TileCoord);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 200.0f, FColor::Red, FString::Printf(TEXT("--> Character placed on Unwalkable tile <--")));
	}
}