#include "AG_PlayableCharacter.h"
#include "AG_ColdNites/Pickup/AG_InventoryComponent.h"
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
}

void AAG_PlayableCharacter::MoveForward() { Super::MoveForward(); }
void AAG_PlayableCharacter::MoveBackward() { Super::MoveBackward(); }
void AAG_PlayableCharacter::MoveRight() { Super::MoveRight(); }
void AAG_PlayableCharacter::MoveLeft() { Super::MoveLeft(); }

void AAG_PlayableCharacter::NextInventoryItem() { InventoryComponent->NextInventoryItem(); }
void AAG_PlayableCharacter::PreviousInventoryItem() { InventoryComponent->PreviousInventoryItem(); }