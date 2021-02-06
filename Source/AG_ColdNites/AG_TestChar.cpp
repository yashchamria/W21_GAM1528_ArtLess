#include "AG_TestChar.h"
#include "AG_PlayerController.h"
#include "Blueprint/UserWidget.h"

AAG_TestChar::AAG_TestChar()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAG_TestChar::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AAG_PlayerController>(GetController());
}

void AAG_TestChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAG_TestChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ESC", IE_Pressed,  this, &AAG_TestChar::EscKeyDown);
}

void AAG_TestChar::EscKeyDown()
{
	if(MainPlayerController && GetWorld()->GetMapName() != L"UEDPIE_0_MainMenu") 
	{
		MainPlayerController->TogglePauseMenu();
	}
}