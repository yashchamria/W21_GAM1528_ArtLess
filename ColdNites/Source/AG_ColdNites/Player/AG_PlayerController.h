/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Jonathan Sime

 Module:  Player Character, UI

 Description -

******************************************************************************************************************/

/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Vrund Soni

 Module:  Player Character, UI

 Description -

******************************************************************************************************************/

/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Xiyang Chen

 Module:  Player Character, UI

 Description -

******************************************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AG_PlayerController.generated.h"

class AAG_ColdNitesGameModeBase;

UCLASS()
class AG_COLDNITES_API AAG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAG_PlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	class AAG_PlayableCharacter* Player;
	class AAG_TileMap* TileMap;
	
///---------------------------------------Player Movement Setup----------------------------------------------------------///
protected:

	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();
	void StopMove();
	
	uint32 bMoveToMouseCursor : 1;

	void MoveToMouseCursor();
	void SetNewMoveDestination(const FVector DestLocation);

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

public:
	void SetCanMove(bool canMove) { bCanPlayerMove = canMove; }
///******************************************************************************************************************///

///---------------------------------------Inventory Setup----------------------------------------------------------///
protected:
	
	void NextInventoryItem();
	void PreviousInventoryItem();

///******************************************************************************************************************///


///---------------------------------------UI Setup----------------------------------------------------------///
public:
	//Reference to the UMG asset in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		TSubclassOf<class UUserWidget> PauseMenuTemplate;

	UUserWidget* PauseMenu; //Variable to hold the widget after creating it

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		TSubclassOf<class UUserWidget> ResOptionsMenuTemplate;

	UUserWidget* ResOptionsMenu;

	bool bPauseMenuVisible;
	bool bResOptionsMenuVisible;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AG_Widgets")
		bool bMainMenuVisible;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		bool bCanPlayerMove;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AG_Widgets")
	void HidePauseMenu();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AG_Widgets")
	void ShowResOptionsMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AG_Widgets")
	void HideResOptionsMenu();

	void ShowPauseMenu();
	void TogglePauseMenu();
	void Esc_KeyDown();
	
///******************************************************************************************************************///
};