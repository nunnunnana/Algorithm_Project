// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SortActor.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
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

	UPROPERTY()
	FString selectedName = ("Selection Sort");

	UPROPERTY(meta = (BindWidget))
	UButton* sortButton;
	UPROPERTY(meta = (BindWidget))
	UButton* shuffleButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* sortComboBox;

	UPROPERTY(EditAnyWhere)
	ASortActor* sortActor;

public:
	UFUNCTION()
	void StartSort();

	UFUNCTION()
	void StartShuffle();

	UFUNCTION()
	void SelectedChange(FString selectedItem, ESelectInfo::Type selectionType);
};
