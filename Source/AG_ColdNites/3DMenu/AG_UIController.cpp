#include "AG_UIController.h"
#include "AG_MenuButton.h"
#include "Kismet/GameplayStatics.h"

AAG_UIController::AAG_UIController()
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;

	bNextClicked = false;
	bPrevClicked = false;
}

void AAG_UIController::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(this, AAG_MenuButton::StaticClass(), Buttons);

	NumButtons = Buttons.Num();
	
	YawVals.Reserve(Buttons.Num());
	RotationRate = 360.f / Buttons.Num();

}

void AAG_UIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bNextClicked)
	{
		RotateOnNextClicked(DeltaSeconds * 200);
	}

	if(bPrevClicked)
	{
		RotateOnPrevClicked(DeltaSeconds * 200);
	}
}

void AAG_UIController::OnNextClicked()
{
	if(NumButtons > 0)
	{
		for(int i = 0; i < NumButtons; i++)
		{
			AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Buttons[i]);
			YawVals.Push(i);
			YawVals[i] = MenuButton->GetActorRotation().Yaw;
		}
	}
	bNextClicked = true;
}

void AAG_UIController::OnPrevClicked()
{
	if (NumButtons > 0)
	{
		for (int i = 0; i < NumButtons; i++)
		{
			AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Buttons[i]);
			YawVals.Push(i);
			YawVals[i] = MenuButton->GetActorRotation().Yaw;
		}
	}
	
	bPrevClicked = true;
}

void AAG_UIController::RotateOnNextClicked(float val)
{
	if (NumButtons > 0)
	{
		for(int i = 0; i < NumButtons; i++)
		{
			AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Buttons[i]);

			const float TargetYaw = YawVals[i] + RotationRate;
			
			if(MenuButton->GetActorRotation().Yaw <= TargetYaw)
			{
				MenuButton->SetActorRotation(MenuButton->GetActorRotation() + FRotator(0.f, val, 0.f));

				if(MenuButton->GetActorRotation().Yaw >= TargetYaw)
				{
					MenuButton->SetActorRotation(FRotator(0.f, TargetYaw, 0.f));
					bNextClicked = false;
				}
			}
		}
	}
}

void AAG_UIController::RotateOnPrevClicked(float val)
{
	if (NumButtons > 0)
	{
		for (int i = 0; i < NumButtons; i++)
		{
			AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Buttons[i]);

			const float TargetYaw = YawVals[i] - RotationRate;

			if (MenuButton->GetActorRotation().Yaw >= TargetYaw)
			{
				MenuButton->SetActorRotation(MenuButton->GetActorRotation() - FRotator(0.f, val, 0.f));

				if (MenuButton->GetActorRotation().Yaw <= TargetYaw)
				{
					MenuButton->SetActorRotation(FRotator(0.f, TargetYaw, 0.f));
					bPrevClicked = false;
				}
			}
		}
	}
}