#include "AG_AIBaseGridCharacter.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "Kismet/GameplayStatics.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/Player/AG_PlayerController.h"
#include "Sound/SoundBase.h"

AAG_AIBaseGridCharacter::AAG_AIBaseGridCharacter()
{
	Tags.Add("AG_AICharacter");
}

void AAG_AIBaseGridCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//static ConstructorHelpers::FObjectFinder<USoundBase>  USB(TEXT("Walk Sound '/Game/Audio/Footsteps/Walk_on_Wood_Tile'"));
	//WalkSound = CreateDefaultSubobject<USoundBase>(TEXT("Walk Sound"));
	//if (USB.Succeeded()) { WalkSound = USB.Object; }
}

void AAG_AIBaseGridCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Getting Player
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player) { PlayerCharacter = Cast<AAG_PlayableCharacter>(Player); }

	//Getting PlayerController
	APlayerController* CurrentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (CurrentController) { PlayerController = Cast<AAG_PlayerController>(CurrentController); }
}

void AAG_AIBaseGridCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAG_AIBaseGridCharacter::MoveRight()
{
	Super::MoveRight();
}

void AAG_AIBaseGridCharacter::MoveLeft()
{
	Super::MoveLeft();
	AAG_PlayableCharacter* OwningActor = Cast<AAG_PlayableCharacter>(GetOwner());
}

void AAG_AIBaseGridCharacter::MoveForward()
{
	Super::MoveForward();
	AAG_PlayableCharacter* OwningActor = Cast<AAG_PlayableCharacter>(GetOwner());
}

void AAG_AIBaseGridCharacter::MoveBackward()
{
	Super::MoveBackward();
	AAG_PlayableCharacter* OwningActor = Cast<AAG_PlayableCharacter>(GetOwner());
}

bool AAG_AIBaseGridCharacter::IsActorInRange(FName ActorTag, FVector InDirection, uint32 TileRange)
{
	FIntPoint CurrentTileCoord = TileMap->GetTileCoord(GetActorLocation());
	FIntPoint NextTileCoord = TileMap->GetNextTileCoord(GetActorLocation(), InDirection, TileRange);

	if (TileMap->IsRegistered(ActorTag, NextTileCoord))
	{
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, "Actor In Range !!!");
		return true;
	}
	return false;
}

bool AAG_AIBaseGridCharacter::bIsPlayerInRange(uint32 TileRange)
{
	for (uint32 i = 1; i <= TileRange; i++)
	{
		if (IsActorInRange("AG_PlayableCharacter", GetActorForwardVector(), i))
		{
			return true;
		}
	}
	return false;
}

bool AAG_AIBaseGridCharacter::IsPlayerInRange()
{
	return IsActorInRange("AG_PlayableCharacter", GetActorForwardVector());
}

void AAG_AIBaseGridCharacter::KnockOutPlayer(FVector ForwardDirection)
{
	if (PlayerCharacter->bIsReached)
	{
		MoveForward();

		AAG_AIBaseGridCharacter* AICharacter = Cast<AAG_AIBaseGridCharacter>(GetInstigator());
		
		if (AICharacter->bIsReached)
		{
			PlayerCharacter->KnockOut(ForwardDirection);
			PlayerController->EnableGamePlayInput(false);

			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Player Caught !!!");
		}
	}
}