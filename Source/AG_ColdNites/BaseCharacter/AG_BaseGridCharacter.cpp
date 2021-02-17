#include "AG_BaseGridCharacter.h"
#include "../TileMap/AG_TileMap.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

AAG_BaseGridCharacter::AAG_BaseGridCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
}

void AAG_BaseGridCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAG_BaseGridCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Getting the Spawned TileMap Actor from the World
	TArray<AActor*> TileMapActor;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_TileMap::StaticClass(), TileMapActor);

	if (TileMapActor.Num() > 0)
	{
		TileMap = Cast<AAG_TileMap>(TileMapActor[0]);
		TargetTileWorldLocation = TileMap->GetTileWorldPosition(TileMap->GetTileCoord(GetActorLocation()));
		
		FIntPoint CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());
		TileMap->Register(this, CurrentTileCoord);
	}

}


void AAG_BaseGridCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetActorRotation(TargetRotation); Rotates the player...Can make it hard to navigate 

	if(bWalk)
	{
		TargetDistance = FVector::Distance(GetActorLocation(), TargetTileWorldLocation);

		if(TargetDistance > TileMap->TileSize.X/2)
		{
			AddMovementInput(TargetDirection);
		}
		else
		{
			bWalk = false;
		}
	}
	 
	//GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("bRotate: %d"), bRotate));
	//GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("TargetRotation: %s"), *TargetRotation.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 0.01, FColor::Orange, FString::Printf(TEXT("GetActorRotation: %s"), *GetActorRotation().ToString()));
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

	if(IsNextTileWalkable)
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