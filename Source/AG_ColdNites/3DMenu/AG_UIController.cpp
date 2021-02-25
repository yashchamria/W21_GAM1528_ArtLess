#include "AG_UIController.h"
#include "AG_MenuButton.h"
#include "Kismet/GameplayStatics.h"

AAG_UIController::AAG_UIController()
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;

	RotationSpeed = 175.0f;  //Increasing this might cause the update to miss the correct snapping location for the button
	
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

	RepositionButtons();
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
	GetCurrentYawValues();
	bNextClicked = true;
}

void AAG_UIController::OnPrevClicked()
{
	GetCurrentYawValues();
	bPrevClicked = true;
}

void AAG_UIController::RepositionButtons()
{
	float Angle = 0.f;
	
	if(MenuButton.Num())
	{
		for(int i = 0; i < MenuButton.Num(); i++)
		{
			MenuButton[i]->SetActorLocation(FVector(0.f));
			MenuButton[i]->SetActorRotation(FRotator(0.f, Angle, 0.f));
			Angle += RotationRate;
		}
	}
}

void AAG_UIController::GetCurrentYawValues()
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