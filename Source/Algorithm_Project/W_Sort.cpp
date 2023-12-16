// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Sort.h"

void UW_Sort::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	sortButton->OnClicked.AddDynamic(this, &UW_Sort::StartSort);
	shuffleButton->OnClicked.AddDynamic(this, &UW_Sort::StartShuffle);

}

void UW_Sort::StartSort()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sort"));
}

void UW_Sort::StartShuffle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Shuffle"));
}
