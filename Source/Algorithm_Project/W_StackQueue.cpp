// Fill out your copyright notice in the Description page of Project Settings.


#include "W_StackQueue.h"

void UW_StackQueue::SetAlertText(FText text)
{
	alertText->SetText(text);
	//MainHUDWidget->GetItemText()->SetText(FText::FromString(alertText));
}
