// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Sort.h"

void UW_Sort::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	sortButton->OnClicked.AddDynamic(this, &UW_Sort::StartSort);

}

void UW_Sort::StartSort()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sort"));
}
