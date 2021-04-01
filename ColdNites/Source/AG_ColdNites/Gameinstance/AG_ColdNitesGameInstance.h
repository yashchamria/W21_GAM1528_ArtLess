// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AG_ColdNitesGameInstance.generated.h"

UCLASS()
class AG_COLDNITES_API UAG_ColdNitesGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "AG_Levels")
	void OpenNextLevel();

	UFUNCTION(BlueprintCallable, Category = "AG_Levels")
	void OpenSameLevel();
};
