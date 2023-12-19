// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Sort.h"

void UW_Sort::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass로 월드에 있는 ASortActor 액터 찾기
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASortActor::StaticClass());
	// ASortActor로 형변환
	sortActor = Cast<ASortActor>(FoundActor);

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
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
