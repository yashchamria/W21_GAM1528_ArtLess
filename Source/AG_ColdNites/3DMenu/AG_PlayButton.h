#pragma once

#include "CoreMinimal.h"
#include "AG_MenuButton.h"
#include "AG_PlayButton.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_PlayButton : public AAG_MenuButton
{
	GENERATED_BODY()

public:
	AAG_PlayButton();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
