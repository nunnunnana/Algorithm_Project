// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SearchLevelManager.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHM_PROJECT_API ASearchLevelManager : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};


