// Fill out your copyright notice in the Description page of Project Settings.


#include "W_StackQueue.h"

void UW_StackQueue::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass�� ���忡 �ִ� AStackQueue ���� ã��
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AStackQueue::StaticClass());
	// AStackQueue�� ����ȯ
	stackqueueActor = Cast<AStackQueue>(FoundActor);

	//stackqueueActor = Cast(UGameplayStatics::GetActorOfClass(GetWorld(), AStackQueue::StaticClass()));
	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	convertButton->OnClicked.AddDynamic(this, &UW_StackQueue::SetButtonText);
	alertText->SetVisibility(ESlateVisibility::Hidden);
	queuePanel->SetVisibility(ESlateVisibility::Hidden);
}
void UW_StackQueue::SetAlertText(FText text)
{
	alertText->SetVisibility(ESlateVisibility::Visible);
	alertText->SetText(text);

	// Ÿ�̸� �ʱ�ȭ
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	// Ÿ�̸� ����
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UW_StackQueue::AdvanceTimer, 1.0f, false, 3.0f);

}

void UW_StackQueue::SetIndexText(int index)
{
	FString indexString = FString::FromInt(index);
	indexText->SetText(FText::FromString(indexString));
}

void UW_StackQueue::AdvanceTimer()
{
	alertText->SetVisibility(ESlateVisibility::Hidden);
}

void UW_StackQueue::SetButtonText()
{
	if (isQueue == true) {
		stackqueueActor->ClearQueue();
		stateText->SetText(FText::FromString("Stack"));
		stackPanel->SetVisibility(ESlateVisibility::Visible);
		queuePanel->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		stackqueueActor->ClearStack();
		SetIndexText(0);
		stateText->SetText(FText::FromString("Queue"));
		stackPanel->SetVisibility(ESlateVisibility::Hidden);
		queuePanel->SetVisibility(ESlateVisibility::Visible);
	}
	isQueue = !isQueue;
}

