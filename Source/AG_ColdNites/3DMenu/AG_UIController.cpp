#include "AG_UIController.h"
#include "AG_MenuButton.h"
#include "Kismet/GameplayStatics.h"

AAG_UIController::AAG_UIController()
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;

	bNextClicked = bPrevClicked = false;
	ip = in = 0;

}

void AAG_UIController::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(this, AAG_MenuButton::StaticClass(), Buttons);

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
	const int NumButtons = Buttons.Num();
	if(NumButtons > 0)
	{
		for(int i = 0; i < NumButtons; i++)
		{
			AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Buttons[i]);
			YawVals[i] = MenuButton->GetActorRotation().Yaw;
		}
		
		//for(AActor* Button : Buttons)
		//{
		//	AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Button);
		//	
		//	FRotator CurrentRotation = MenuButton->GetActorRotation();
		//
		//	
		//	FRotator TargetRotation = CurrentRotation + FRotator(0.f, 360.f / NumButtons, 0.f);
		//	const float DeltaSeconds = GetWorld()->GetDeltaSeconds();
		//	
		//	//MenuButton->GetButtonMesh()->SetRelativeRotation(MenuButton->GetButtonMesh()->GetRelativeRotation());
		//	//MenuButton->SetActorRotation(MenuButton->GetActorRotation() + FRotator (0.f, 360.f / NumButtons, 0.f));
		//	//MenuButton->SetActorRotation(FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 50.f));
		//}
	}

	
	bNextClicked = true;
}

void AAG_UIController::OnPrevClicked()
{
	const int NumButtons = Buttons.Num();
	if (NumButtons > 0)
	{
		for (auto Button : Buttons)
		{
			Button->SetActorRotation(Button->GetActorRotation() + FRotator(0.f, -360.f / NumButtons, 0.f));
		}
	}
}

void AAG_UIController::RotateOnNextClicked(float val)
{
	const int NumButtons = Buttons.Num();

	if (NumButtons > 0)
	{
		for(int i = 0; i < NumButtons; i++)
		{
			AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Buttons[i]);

			FRotator CurrentRotation = MenuButton->GetActorRotation();
			FRotator TargetRotation = CurrentRotation + FRotator(0.f, 360.f / NumButtons, 0.f);

			const float TargetYaw = YawVals[i] + 360.f / NumButtons;
			
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
		
		//for (AActor* Button : Buttons)
		//{
		//	AAG_MenuButton* MenuButton = Cast<AAG_MenuButton>(Button);
		//
		//	FRotator CurrentRotation = MenuButton->GetActorRotation();
		//	FRotator TargetRotation = CurrentRotation + FRotator(0.f, 360.f / NumButtons, 0.f);
		//	const float DeltaSeconds = GetWorld()->GetDeltaSeconds();
		//
		//	if(MenuButton->GetActorRotation().Yaw <= (MenuButton->GetActorRotation().Yaw + 120.f))
		//	{
		//		MenuButton->SetActorRotation(MenuButton->GetActorRotation() + FRotator (0.f, val, 0.f));
		//	}
		//	
		//	if (MenuButton->GetActorRotation().Yaw >= (MenuButton->GetActorRotation().Yaw + 120.f))
		//	{
		//		bNextClicked = false;
		//	}
		//	
		//	//MenuButton->SetActorRotation(FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 50.f));
		//}
	}
}

void AAG_UIController::RotateOnPrevClicked(float val)
{
	
}

//SnapToPosition(float minRange, float maxRange, float correctvalue)
//{
//	if(yaw > maxRange)
//}