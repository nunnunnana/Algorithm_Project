// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Search.h"

void UW_Search::NativeConstruct()
{
	Super::NativeConstruct();

	// GetActorOfClass로 월드에 있는 ASearch 액터 찾기
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASearch::StaticClass());
	// ASortActor로 형변환
	search = Cast<ASearch>(FoundActor);
	
	// 버튼 클릭시 호출될 델리게이트에 함수를 등록
	startButton->OnClicked.AddDynamic(this, &UW_Search::StartSearch);
	resetButton->OnClicked.AddDynamic(this, &UW_Search::StartReset);
	searchComboBox->OnSelectionChanged.AddDynamic(this, &UW_Search::SelectedChange);
}

// 선택한 ComboBox에 맞는 알고리즘 실행
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

// 선택한 정렬 알고리즘 이름 설정
void UW_Search::SelectedChange(FString selectedItem, ESelectInfo::Type selectionType)
{
	selectedName = selectedItem;
}