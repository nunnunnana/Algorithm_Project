// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Search.h"

void UW_Search::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass�� ���忡 �ִ� ASearch ���� ã��
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASearch::StaticClass());
	// ASortActor�� ����ȯ
	search = Cast<ASearch>(FoundActor);
	
	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ���
	startButton->OnClicked.AddDynamic(this, &UW_Search::StartSearch);
	resetButton->OnClicked.AddDynamic(this, &UW_Search::StartReset);
	searchComboBox->OnSelectionChanged.AddDynamic(this, &UW_Search::SelectedChange);
}

// ������ ComboBox�� �´� �˰��� ����
void UW_Search::StartSearch()
{
	if (selectedName == ("BFS"))
		search->StartBFS();
	else if (selectedName == ("DFS"))
		search->StartDFS(nullptr);
	else if (selectedName == ("Dijkstra"))
		search->StartDijkstra();
	else if (selectedName == ("A*"))
		search->StartAstar();
}

void UW_Search::StartReset()
{
	search->ResetMap();
}

// ������ ���� �˰��� �̸� ����
void UW_Search::SelectedChange(FString selectedItem, ESelectInfo::Type selectionType)
{
	selectedName = selectedItem;
}