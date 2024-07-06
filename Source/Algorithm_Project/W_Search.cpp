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


	search->OnDestinationReached.BindUFunction(this, FName("CallDeleFunc_OnDestinationReached"));
	search->OnDestinationUnreached.BindUFunction(this, FName("CallDeleFunc_OnDestinationUnreached"));

}

// ���� ��������Ʈ �Լ� ����
void UW_Search::CallDeleFunc_OnDestinationReached()
{
	alertText->SetText(FText::FromString("Target reached"));
	ActivateSuccess();
	isStarted = false;
}

// ���� ��������Ʈ �Լ� ����
void UW_Search::CallDeleFunc_OnDestinationUnreached()
{
	alertText->SetText(FText::FromString("Unable to connect to destination"));
	ActivateWarning();
	isStarted = false;
}

// ������ ComboBox�� �´� �˰��� ����
void UW_Search::StartSearch()
{
	if (!isStarted) {
		isStarted = true;
		if (!isReset) {
			search->ResetMap();
		}
		isReset = false;
		if (selectedName == ("BFS"))
			search->StartBFS();
		else if (selectedName == ("DFS"))
			search->StartDFS(nullptr);
		else if (selectedName == ("Dijkstra")) {
			search->StartDijkstra();
			search->ActivateDijkstra();
		}
		else if (selectedName == ("A*")) {
			search->StartAstar(nullptr);
			search->ActivateAStar();
		}
	
	}
}

// �� �ʱ�ȭ �Լ� ȣ��
void UW_Search::StartReset()
{
	if (!isStarted) {
		search->ResetMap();
		isReset = true;
	}
}

// ������ ���� �˰��� �̸� ����
void UW_Search::SelectedChange(FString selectedItem, ESelectInfo::Type selectionType)
{
	selectedName = selectedItem;
}

void UW_Search::ActivateWarning()
{
	PlayAnimation(alertWarning);
}

void UW_Search::ActivateSuccess()
{
	PlayAnimation(alertSuccess);
}
