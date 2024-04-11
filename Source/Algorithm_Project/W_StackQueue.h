// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "StackQueue.h"
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
		UCanvasPanel* alertPanel;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* alertWarning;

	UPROPERTY(meta = (BindWidget))
		UButton* pushButton;

	UPROPERTY(meta = (BindWidget))
		UButton* popButton;

	UPROPERTY(meta = (BindWidget))
		UButton* convertButton;
	
	UPROPERTY(meta = (BindWidget))
		UTextBlock* stateText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* indexText;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* stackPanel;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* queuePanel;

	UPROPERTY()
		AStackQueue* stackqueueActor;

	FTimerHandle Timer;

public:
	
	UFUNCTION()
		void SetAlertText(FText text);

	UFUNCTION()
		void SetIndexText(int index);

	UFUNCTION()
		void SetButtonText();

	UFUNCTION()
		void PressPushButton();

	UFUNCTION()
		void PressPopButton();

};
