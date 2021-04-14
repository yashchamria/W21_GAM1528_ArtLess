#include "AG_BaseGridCharacter.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

AAG_BaseGridCharacter::AAG_BaseGridCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxWalkSpeed = 275.0f;
	ErrorRange = 6.5f; //Don't lower it any further...movement will might miss some update calls and not stop
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);	

	//Temp Hack to display desired mesh without skeletal animation
	AG_TempMesh = CreateDefaultSubobject<UStaticMeshComponent>("Temp Mesh");
	AG_TempMesh->SetCollisionProfileName("NoCollision");
	AG_TempMesh->SetupAttachment(RootComponent);
	
	//static ConstructorHelpers::FObjectFinder<USoundBase> USB(TEXT("/Game/Sound/Walk_on_Wood_Tile.Walk_on_Wood_Tile"));
	//WalkSound = CreateDefaultSubobject<USoundBase>(TEXT("Walk Sound"));
	//if (USB.Succeeded()) { WalkSound = USB.Object; }
}

void AAG_BaseGridCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//Getting TileMap
	TArray<AActor*> TileMapActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_TileMap::StaticClass(), TileMapActor);
	if (TileMapActor.Num() > 0) { TileMap = Cast<AAG_TileMap>(TileMapActor[0]); }

	if (TileMap)
	{
		TargetTileWorldLocation = TileMap->GetTileWorldPosition(TileMap->GetTileCoord(GetActorLocation()));

		FIntPoint CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());
		if (bShouldRegister) { TileMap->Register(this, CurrentTileCoord); }

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
		bMoveSucceeded = true;
		
		TargetDistance.X = TargetTileWorldLocation.X - GetActorLocation().X;
		TargetDistance.Y = TargetTileWorldLocation.Y - GetActorLocation().Y;

		if ((TargetDistance.X > ErrorRange || TargetDistance.X < -ErrorRange) || (TargetDistance.Y > ErrorRange || TargetDistance.Y < -ErrorRange))
		{
			AddMovementInput(TargetDirection);
			bIsReached = false;
		}
		else
		{
			bIsReached = true;
			bWalk = false;
		}
	}

	if (bRotate)
	{
		SetActorRotation(TargetRotation);
		bRotate = false;
	}

	KnockOutDelay -= DeltaTime;
	if (bKnockOut && KnockOutDelay <= 0.0f)
	{
		AG_TempMesh->SetRelativeRotation(KnockedOutAngle);

		if (bShouldDestroy)
		{
			bDestroy = true;
			DestroyDelay = 1.0f;
		}
	}

	DestroyDelay -= DeltaTime;
	if (bDestroy && DestroyDelay <= 0.0f) { Destroy(); }
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

		if (bShouldRegister)
		{
			TileMap->UnRegister(this, CurrentTileCoord);
			TileMap->Register(this, NextTileCoord);
		}
	}
}

void AAG_BaseGridCharacter::MoveForward()
{
	//bRotate = false;
	MoveTile(GetActorForwardVector());
}

void AAG_BaseGridCharacter::MoveBackward()
{
	//bRotate = true;
	TargetRotation = GetActorRotation() + FRotator(0.0f, 180.0f, 0.0f);
	MoveTile(-GetActorForwardVector());
}

void AAG_BaseGridCharacter::MoveRight()
{
	//bRotate = true;
	TargetRotation = GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f);
	MoveTile(GetActorRightVector());
}

void AAG_BaseGridCharacter::MoveLeft()
{
	//bRotate = true;
	TargetRotation = GetActorRotation() + FRotator(0.0f, -90.0f, 0.0f);
	MoveTile(-GetActorRightVector());
}

void AAG_BaseGridCharacter::Teleport()
{
	FIntPoint CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());

	bool IsCurrentTileTransportable = TileMap->GetTileProperty(CurrentTileCoord, AG_TileProperty::IsTransportable);

	if(IsCurrentTileTransportable)
	{
		FIntPoint TargetTileCoord = TileMap->GetSewerPairCoord(CurrentTileCoord);
		FVector TargetTileWorldPosition = TileMap->GetTileWorldPosition(TargetTileCoord);

		SetActorLocation(TargetTileWorldPosition);

		if (bShouldRegister)
		{
			TileMap->UnRegister(this, CurrentTileCoord);
			TileMap->Register(this, TargetTileCoord);
		}
		
		bIsReached = true;
		bMoveSucceeded = true;
	}
}

void AAG_BaseGridCharacter::Rotate(float Rotation)
{
	if (!bAlreadyRotated)
	{
		bAlreadyRotated = true;
		bRotate = true;
		TargetRotation = GetActorRotation() + FRotator(0.0f, Rotation, 0.0f);
	}
}

void AAG_BaseGridCharacter::KnockOut(FVector FallDirection)
{
	bIsKnockedOut = true;

	bKnockOut = true;
	KnockOutDelay = 1.65f;
	KnockedOutAngle = FallDirection.Rotation() + FRotator(0.0f , 0.0f, -80.0f);
}

//void AAG_BaseGridCharacter::WalkSoundEffect()
//{
//	if (WalkSound) { UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), WalkSound, GetActorLocation()); }
//}

void AAG_BaseGridCharacter::Animate(){}

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

		if (bShouldRegister) { TileMap->Register(this, TileCoord); }
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 200.0f, FColor::Red, FString::Printf(TEXT("Character placed on Unwalkable tile")));
	}
}

void AAG_BaseGridCharacter::ResetOnTurnEnd()
{
	bAlreadyRotated = false;
	bMoveSucceeded = false;
}