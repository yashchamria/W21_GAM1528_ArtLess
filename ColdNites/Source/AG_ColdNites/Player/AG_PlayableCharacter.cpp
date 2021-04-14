#include "AG_PlayableCharacter.h"
#include "AG_ColdNites/Pickup/AG_InventoryComponent.h"
#include "AG_ColdNites/AI/AG_AIBaseGridCharacter.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
//#include "Components/AudioComponent.h"
//#include "Kismet/GameplayStatics.h"


AAG_PlayableCharacter::AAG_PlayableCharacter()
{
	InventoryComponent = CreateDefaultSubobject<UAG_InventoryComponent>("Player Inventory");

	ItemHolder = CreateDefaultSubobject<USceneComponent>("ItemHolder");
	ItemHolder->AttachTo(GetRootComponent());
	ItemHolder->SetRelativeLocation(FVector(0, 0, 150.f));

	//static ConstructorHelpers::FObjectFinder<USoundBase> USB(TEXT("/Game/Sound/PickUp.PickUp"));
	//PickUpSound = CreateDefaultSubobject<USoundBase>(TEXT("Pick Up Sound"));
	//if (USB.Succeeded()) { PickUpSound = USB.Object; }

	bShouldDestroy = false;
	Tags.Add("AG_PlayableCharacter");
}

void AAG_PlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAG_PlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TileMap->IsRegistered("AG_AICharacter", TileMap->GetTileCoord(GetActorLocation())) && this->bIsKnockedOut == false)
	{
		AActor* Ai = TileMap->GetAllRegisteredActors(TileMap->GetTileCoord(GetActorLocation()));
		if (Ai != nullptr)
		{
			AAG_AIBaseGridCharacter* AiToKnockout = Cast<AAG_AIBaseGridCharacter>(Ai);
			if (AiToKnockout->IsPlayerInRange() == false && AiToKnockout->bIsKnockedOut == false)
			{
				KnockOutAI(AiToKnockout);
			}
		}
	}
}

void AAG_PlayableCharacter::MoveForward() { Super::MoveForward(); }
void AAG_PlayableCharacter::MoveBackward() { Super::MoveBackward(); }

void AAG_PlayableCharacter::TransportThroughSewer()
{
	Teleport();
}

void AAG_PlayableCharacter::MoveRight() { Super::MoveRight(); }
void AAG_PlayableCharacter::MoveLeft() { Super::MoveLeft(); }

void AAG_PlayableCharacter::KnockOutAI(AAG_AIBaseGridCharacter* AiToKnockout)
{
	AiToKnockout->KnockOut(AiToKnockout->GetActorForwardVector());
}

void AAG_PlayableCharacter::NextInventoryItem() { InventoryComponent->NextInventoryItem(); }
void AAG_PlayableCharacter::PreviousInventoryItem() { InventoryComponent->PreviousInventoryItem(); }