// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_StackQueue.generated.h"


UCLASS()
class ALGORITHM_PROJECT_API UW_StackQueue : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	bool isQueue = false;

private:
	void AdvanceTimer();

	UPROPERTY(meta = (BindWidget))
		UTextBlock* alertText;

	UPROPERTY(meta = (BindWidget))
		UButton* convertButton;
	
	UPROPERTY(meta = (BindWidget))
		UTextBlock* stateText;

	FTimerHandle Timer;

public:
	
	UFUNCTION()
		void SetAlertText(FText text);

	UFUNCTION()
		void SetButtonText();
};
