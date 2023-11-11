// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "W_StackQueue.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHM_PROJECT_API UW_StackQueue : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* alertText;

public:
	FORCEINLINE UTextBlock* GetItemText() { return alertText; };

	UFUNCTION(BlueprintCallable)
		void SetAlertText(FText text);
};
