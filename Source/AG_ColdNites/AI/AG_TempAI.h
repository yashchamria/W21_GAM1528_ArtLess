#pragma once

#include "CoreMinimal.h"
#include "../BaseGridClasses/AG_BaseGridCharacter.h"
#include "AG_TempAI.generated.h"

UCLASS()
class AG_COLDNITES_API AAG_TempAI : public AAG_BaseGridCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AG_Components")
		class UStaticMeshComponent* AG_Mesh;
	
	float TurnTimer;
	
public:
	AAG_TempAI();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
