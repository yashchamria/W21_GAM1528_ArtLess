#include "AG_UIController.h"
#include "AG_MenuButton.h"
#include "Kismet/GameplayStatics.h"

AAG_UIController::AAG_UIController()
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;

	RotationSpeed = 200.0f;  //Increasing this might cause the update to miss the correct snapping location for the button
	
	bNextClicked = false;
	bPrevClicked = false;

}

void AAG_UIController::BeginPlay()
{
	SetShowMouseCursor(true);
	
	TArray<AActor*> ButtonActors;
	UGameplayStatics::GetAllActorsOfClass(this, AAG_MenuButton::StaticClass(), ButtonActors);

	if(ButtonActors.Num() > 0)
	{
		for (int i = 0; i < ButtonActors.Num(); i++)
		{
			MenuButton.Insert(Cast<AAG_MenuButton>(ButtonActors[i]), i);
		}
		
		YawValues.Reserve(MenuButton.Num());
		RotationRate = 360.f / MenuButton.Num();
	}
}

void AAG_UIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bNextClicked)
	{
		RotateOnNextClicked(DeltaSeconds * RotationSpeed);
	}

	if(bPrevClicked)
	{
		RotateOnPrevClicked(DeltaSeconds * RotationSpeed);
	}
}

void AAG_UIController::OnNextClicked()
{
	UpdateNewYawValues();
	bNextClicked = true;
}

void AAG_UIController::OnPrevClicked()
{
	UpdateNewYawValues();
	bPrevClicked = true;
}

void AAG_UIController::HideResOptionsMenu_Implementation()
{
	bResOptionsVisible = true;
}

void AAG_UIController::UpdateNewYawValues()
{
	if (MenuButton.Num() > 0)
	{
		for (int i = 0; i < MenuButton.Num(); i++)
		{
			YawValues.Insert(MenuButton[i]->GetActorRotation().Yaw, i);
		}
	}

}
void AAG_UIController::RotateOnNextClicked(float YawValue)
{
	for(int i = 0; i < MenuButton.Num(); i++)
	{
		const float TargetYaw = YawValues[i] + RotationRate;
		
		if(MenuButton[i]->GetActorRotation().Yaw <= TargetYaw)
		{
			MenuButton[i]->SetActorRotation(MenuButton[i]->GetActorRotation() + FRotator(0.f, YawValue, 0.f));

			if(MenuButton[i]->GetActorRotation().Yaw >= TargetYaw)
			{
				MenuButton[i]->SetActorRotation(FRotator(0.f, TargetYaw, 0.f));
				bNextClicked = false;
			}
		}
	}
}

void AAG_UIController::RotateOnPrevClicked(float YawValue)
{
	for (int i = 0; i < MenuButton.Num(); i++)
	{
		const float TargetYaw = YawValues[i] - RotationRate;

		if (MenuButton[i]->GetActorRotation().Yaw >= TargetYaw)
		{
			MenuButton[i]->SetActorRotation(MenuButton[i]->GetActorRotation() - FRotator(0.f, YawValue, 0.f));

			if (MenuButton[i]->GetActorRotation().Yaw <= TargetYaw)
			{
				MenuButton[i]->SetActorRotation(FRotator(0.f, TargetYaw, 0.f));
				bPrevClicked = false;
			}
		}
	}
}