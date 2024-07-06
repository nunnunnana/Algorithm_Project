// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Search.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "W_Search.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHM_PROJECT_API UW_Search : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

private:

	UPROPERTY()
	FString selectedName = ("BFS");

	UPROPERTY(meta = (BindWidget))
	UButton* startButton;
	UPROPERTY(meta = (BindWidget))
	UButton* resetButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* searchComboBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* alertText;

	UPROPERTY(EditAnyWhere)
	ASearch* search;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* alertWarning;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* alertSuccess;

	bool isStarted = false;

	bool isReset= true;

	UFUNCTION()
	void CallDeleFunc_OnDestinationReached();
	UFUNCTION()
	void CallDeleFunc_OnDestinationUnreached();

public:
	UFUNCTION()
	void StartSearch();

	UFUNCTION()
	void StartReset();

	UFUNCTION()
	void SelectedChange(FString selectedItem, ESelectInfo::Type selectionType);

	UFUNCTION()
	void ActivateWarning();

	UFUNCTION()
	void ActivateSuccess();
};
