// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Sort.h"

void UW_Sort::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	sortButton->OnClicked.AddDynamic(this, &UW_Sort::StartSort);

}

void UW_Sort::StartSort()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sort"));
}
