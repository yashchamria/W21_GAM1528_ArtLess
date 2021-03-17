#include "AG_TemporaryWinLoseHandlerAlpha1.h"
#include "AG_ColdNites/TileMap/AG_TileMap.h"
#include "AG_ColdNites/Player/AG_PlayableCharacter.h"
#include "AG_ColdNites/Player/AG_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AAG_TemporaryWinLoseHandlerAlpha1::AAG_TemporaryWinLoseHandlerAlpha1()
{
	PrimaryActorTick.bCanEverTick = true;

	bLockLocation = true;
}

void AAG_TemporaryWinLoseHandlerAlpha1::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TileMapActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAG_TileMap::StaticClass(), TileMapActor);

	Tilemap = Cast<AAG_TileMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AAG_TileMap::StaticClass()));

	if (TileMapActor.Num() > 0)
	{
		Tilemap = Cast<AAG_TileMap>(TileMapActor[0]);
	}

	Player = Cast<AAG_PlayableCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AAG_PlayableCharacter::StaticClass()));
	PlayerController = Cast<AAG_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AAG_TemporaryWinLoseHandlerAlpha1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FIntPoint CurrentTileCoord = Tilemap->GetTileCoord(Player->GetActorLocation());

	if(Tilemap->GetTileProperty(CurrentTileCoord, AG_TileProperty::IsWinTile))
	{
		bWon = true;
		
		if (WinWidgetTemplate)
		{
			WinWidget = CreateWidget<UUserWidget>(PlayerController, WinWidgetTemplate);
			WinWidget->AddToViewport();
			WinWidget->SetVisibility(ESlateVisibility::Visible);
		}

		PlayerController->EnableGamePlayInput(false);
	}

	if(Player->bKnockOut && !bWon)
	{
		LoseDelay -= DeltaTime;
		if(LoseDelay <= 0.f)
		{
			if (WinWidgetTemplate)
			{
				LoseWidget = CreateWidget<UUserWidget>(PlayerController, LoseWidgetTemplate);
				LoseWidget->AddToViewport();
				LoseWidget->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}