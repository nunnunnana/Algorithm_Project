// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Sort.h"

void UW_Sort::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass�� ���忡 �ִ� ASortActor ���� ã��
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASortActor::StaticClass());
	// ASortActor�� ����ȯ
	sortActor = Cast<ASortActor>(FoundActor);

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ���
	sortButton->OnClicked.AddDynamic(this, &UW_Sort::StartSort);
	shuffleButton->OnClicked.AddDynamic(this, &UW_Sort::StartShuffle);
	sortComboBox->OnSelectionChanged.AddDynamic(this, &UW_Sort::SelectedChange);
}

// ������ ComboBox�� �´� �˰��� ����
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

// ������ ���� �˰��� �̸� ����
void UW_Sort::SelectedChange(FString selectedItem, ESelectInfo::Type selectionType)
{
	selectedName = selectedItem;
}
