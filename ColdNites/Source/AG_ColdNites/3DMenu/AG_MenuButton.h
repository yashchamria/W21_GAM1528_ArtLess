/******************************************************************************************************************
Team - ArtLess Games - Section 010

Name - Vrund Soni

Module: Menu System	

Description - Single 3D button actor used in 3D Menu

******************************************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AG_MenuButton.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_MenuButton : public AActor
{
	GENERATED_BODY()
	
public:	
	AAG_MenuButton();

	UPROPERTY(VisibleInstanceOnly, Category = "AG_Menu")
		class USceneComponent* ButtonRootTransformation;
	
	UPROPERTY(EditInstanceOnly, Category = "AG_Menu")
		class UStaticMeshComponent* ButtonMesh;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
