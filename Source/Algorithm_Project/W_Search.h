// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Search.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
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
	FString selectedName = ("Selection Sort");

	UPROPERTY(meta = (BindWidget))
	UButton* startButton;
	UPROPERTY(meta = (BindWidget))
	UButton* resetButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* searchComboBox;

	UPROPERTY(EditAnyWhere)
	ASearch* search;

public:
	UFUNCTION()
	void StartSearch();

	UFUNCTION()
	void StartReset();

	UFUNCTION()
	void SelectedChange(FString selectedItem, ESelectInfo::Type selectionType);
};
