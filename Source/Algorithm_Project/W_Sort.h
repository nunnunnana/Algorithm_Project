// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "W_Sort.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHM_PROJECT_API UW_Sort : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

private:

	UPROPERTY(meta = (BindWidget))
	UButton* sortButton;

public:
	UFUNCTION()
	void StartSort();

};
