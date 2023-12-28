// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Sort.h"

void UW_Sort::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass로 월드에 있는 ASortActor 액터 찾기
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASortActor::StaticClass());
	// ASortActor로 형변환
	sortActor = Cast<ASortActor>(FoundActor);

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록
	sortButton->OnClicked.AddDynamic(this, &UW_Sort::StartSort);
	shuffleButton->OnClicked.AddDynamic(this, &UW_Sort::StartShuffle);
	sortComboBox->OnSelectionChanged.AddDynamic(this, &UW_Sort::SelectedChange);
}

// 선택한 ComboBox에 맞는 알고리즘 실행
void UW_Sort::StartSort()
{
	if (selectedName == ("Selection Sort"))
		sortActor->SelectionSort();
	else if (selectedName == ("Injection Sort"))
		sortActor->InjectionSort();
	else if (selectedName == ("Bubble Sort"))
		sortActor->BubbleSort();
	else if (selectedName == ("Merge Sort"))
		sortActor->MergeSort();
	else if (selectedName == ("Quick Sort"))
		sortActor->QuickSort();
}

void UW_Sort::StartShuffle()
{
	sortActor->ShuffleArray();
}

// 선택한 정렬 알고리즘 이름 설정
void UW_Sort::SelectedChange(FString selectedItem, ESelectInfo::Type selectionType)
{
	selectedName = selectedItem;
}
