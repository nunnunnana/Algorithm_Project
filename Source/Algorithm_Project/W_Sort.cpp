// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Sort.h"

void UW_Sort::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass�� ���忡 �ִ� ASortActor ���� ã��
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASortActor::StaticClass());
	// ASortActor�� ����ȯ
	sortActor = Cast<ASortActor>(FoundActor);

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	sortButton->OnClicked.AddDynamic(this, &UW_Sort::StartSort);
	shuffleButton->OnClicked.AddDynamic(this, &UW_Sort::StartShuffle);

}

void UW_Sort::StartSort()
{
	sortActor->SelectionSort();
}

void UW_Sort::StartShuffle()
{
	sortActor->ShuffleArray();
}
