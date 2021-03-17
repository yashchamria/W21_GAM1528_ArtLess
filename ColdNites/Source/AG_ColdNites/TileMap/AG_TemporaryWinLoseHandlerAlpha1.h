#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_TemporaryWinLoseHandlerAlpha1.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_TemporaryWinLoseHandlerAlpha1 : public AActor
{
	GENERATED_BODY()
	
public:	
	AAG_TemporaryWinLoseHandlerAlpha1();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	class UUserWidget* WinWidget;
	UUserWidget* LoseWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		TSubclassOf<UUserWidget> WinWidgetTemplate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		TSubclassOf<UUserWidget> LoseWidgetTemplate;

private:
	class AAG_PlayableCharacter* Player;
	class AAG_PlayerController* PlayerController;
	class AAG_TileMap* Tilemap;

	bool bWon = false;
	float LoseDelay = 1.65f;
	bool bPlayerKnockedOut = false;
};
