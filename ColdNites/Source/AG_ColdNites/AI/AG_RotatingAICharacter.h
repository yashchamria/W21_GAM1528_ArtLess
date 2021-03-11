#pragma once

#include "CoreMinimal.h"
#include "AG_ColdNites/BaseGridClasses/AG_AIBaseGridCharacter.h"
#include "AG_RotatingAICharacter.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_RotatingAICharacter : public AAG_AIBaseGridCharacter
{
	GENERATED_BODY()

public:
	AAG_RotatingAICharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
