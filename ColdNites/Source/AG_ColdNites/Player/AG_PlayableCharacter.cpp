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

	bShouldDestroy = false;
	Tags.Add("AG_PlayableCharacter");

	static ConstructorHelpers::FObjectFinder<USoundBase> USB(TEXT("Walk Sound '/Game/Audio/Footsteps/Walk2'"));
	WalkSound = CreateDefaultSubobject<USoundBase>(TEXT("Walk Sound"));
	if (USB.Succeeded()) { WalkSound = USB.Object; }
}

void AAG_PlayableCharacter::BeginPlay() { Super::BeginPlay(); }

void AAG_PlayableCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AAG_PlayableCharacter::MoveForward()  { Super::MoveForward();  }
void AAG_PlayableCharacter::MoveBackward() { Super::MoveBackward(); }
void AAG_PlayableCharacter::MoveRight()    { Super::MoveRight();    }
void AAG_PlayableCharacter::MoveLeft()     { Super::MoveLeft();     }

void AAG_PlayableCharacter::TransportThroughSewer() { Teleport(); }

void AAG_PlayableCharacter::AIKnockOut(FIntPoint TileCoord)
{
	if (TileMap->IsRegistered("AG_AICharacter", TileCoord))
	{
 		TArray<AActor*> RegisteredAIActors;

		TileMap->GetAllRegisteredActorArrayOfTag(TileCoord, "AG_AICharacter" , RegisteredAIActors);

		if(RegisteredAIActors.Num() > 0)
		{
			for(AActor* AIActors : RegisteredAIActors)
			{
				AAG_AIBaseGridCharacter* AI = Cast<AAG_AIBaseGridCharacter>(AIActors);

				if (AI) { AI->KnockOut(GetActorForwardVector()); }
			}
 		}
	}
}

void AAG_PlayableCharacter::NextInventoryItem() { InventoryComponent->NextInventoryItem(); }
void AAG_PlayableCharacter::PreviousInventoryItem() { InventoryComponent->PreviousInventoryItem(); }