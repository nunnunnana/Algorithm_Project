// Fill out your copyright notice in the Description page of Project Settings.


#include "Search.h"

// Sets default values
ASearch::ASearch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findMat(TEXT("/Script/Engine.Material'/Game/Asset/Material/M_Base_Green.M_Base_Green'"));
	greenMat = findMat.Object;
}

// Called when the game starts or when spawned
void ASearch::BeginPlay()
{
	Super::BeginPlay();
	DrawMap();
}


// Called every frame
void ASearch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASearch::DrawMap()
{
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			if (j == width && i == height) {
				// spawn end point
				FName path = TEXT("Class'/Game/Search/BP_Search_EndPoint.BP_Search_EndPoint_C'");
				UClass* GenerateBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));
				FVector location(i * 100, j * 100, 0);
				FRotator rotation(0, 0, 0);
				FActorSpawnParameters SpawnParams;
				ASearch_Points* end = (ASearch_Points*)GetWorld()->SpawnActor<ASearch_Points>(GenerateBP, location, rotation, SpawnParams);
				arrPoints.Add(end);
			}
			else if(j == 0 && i == 0) {
				// spawn start point
				FName path = TEXT("Class'/Game/Search/BP_Search_StartPoint.BP_Search_StartPoint_C'");
				UClass* GenerateBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));
				FVector location(i * 100, j * 100, 0);
				FRotator rotation(0, 0, 0);
				FActorSpawnParameters SpawnParams;
				startPoint = (ASearch_Points*)GetWorld()->SpawnActor<ASearch_Points>(GenerateBP, location, rotation, SpawnParams);
			}
			else if (FMath::RandRange(0, distribution) != 0) {
				// spawn points
				FVector location(i * 100, j * 100, 0);
				FRotator rotation(0, 0, 0);
				FActorSpawnParameters SpawnParams;
				ASearch_Points* points = (ASearch_Points*)GetWorld()->SpawnActor<ASearch_Points>(ASearch_Points::StaticClass(), location, rotation, SpawnParams);
				arrPoints.Add(points);
			}
			else {
				// spawn wall
				FName path = TEXT("Class'/Game/Search/BP_Search_Wall.BP_Search_Wall_C'");
				UClass* GenerateBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));
				FVector location(i * 100, j * 100, 0);
				FRotator rotation(0, 0, 0);
				FActorSpawnParameters SpawnParams;
				ASearch_Points* wall = (ASearch_Points*)GetWorld()->SpawnActor<ASearch_Points>(GenerateBP, location, rotation, SpawnParams);
				arrPoints.Add(wall);
			}
		}
	}
}

void ASearch::ResetMap()
{
	TArray<AActor*> destroyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASearch_Points::StaticClass(), destroyActors);
	for (AActor* arr : destroyActors)
	{
		arr->Destroy();
	}
	isfindEndPoint = false;
	arrPoints.Empty();
	arrCurrentCell.Empty();
	DrawMap();

}

void ASearch::StartBFS()
{
	// ������ �Ǵ� point ����
	currentCell = startPoint;
	arrNeighborCell.Empty();
	arrCurrentCell.Add(currentCell);
	// 0.1�� ���� SetSelectionSortColor �Լ� ����
	GetWorld()->GetTimerManager().SetTimer(bfsTimer, this, &ASearch::BFS, 0.1f, true, 0.0f);
}

void ASearch::BFS()
{
	if (arrCurrentCell.IsEmpty() != true) {
		// arrCurrentCell�� ù ��° �ε����� �������� �����ϰ� ù ��° �ε��� ����
		currentCell = arrCurrentCell[0];
		arrCurrentCell.RemoveAt(0);
		FindNeighborCell();

		// CellArray�� End point �ִ��� Ȯ��
		for (ASearch_Points* arr : arrNeighborCell)
		{
			if (arr->isEndpoint == true) {
				isfindEndPoint = true;
			}
			else {
				arr->SetVisited();
				arrCurrentCell.Add(arr);
				arrTotalCell.Add(arr);
			}
		}

		// EntPoint�� ���������� �湮�ߴ� Cell�� ���� ����
		if (isfindEndPoint == true) {
			for (ASearch_Points* arr : arrTotalCell)
			{
				if (arr->isVisited == true) {
					arr->SetMaterial(greenMat);
				}
			}
			arrTotalCell.Empty();
			GetWorld()->GetTimerManager().ClearTimer(bfsTimer);
			OnDestinationReached.Execute();
		}
		else {
			// ��ó Cell Ž���ؼ� ���� �迭 �ʱ�ȭ
			arrNeighborCell.Empty();
		}
		
	}
	else {
		// EndPoint�� ��ã���� ��
		GetWorld()->GetTimerManager().ClearTimer(bfsTimer);
		arrTotalCell.Empty();
		OnDestinationUnreached.Execute();
	}
}

FAsyncCoroutine ASearch::StartDFS(ASearch_Points* point)
{
	// ������ �Ǵ� point ����
	if (point != nullptr) {
		currentCell = point;
	}
	else {
		currentCell = startPoint;
	}

	arrNeighborCell.Empty();
	FindNeighborCell();

	// CellArray�� End point �ִ��� Ȯ��
	for (ASearch_Points* arr : arrNeighborCell)
	{
		if (arr->isEndpoint == true) {
			isfindEndPoint = true;
		}
		else {
			arrCurrentCell.Add(arr);
		}
	}

	// EntPoint�� ���������� �湮�ߴ� Cell�� ���� ����
	if (isfindEndPoint == true) {
		for (ASearch_Points* arr : arrCurrentCell)
		{
			if (arr->isVisited == true) {
				arr->SetMaterial(greenMat);
			}
		}
		OnDestinationReached.Execute();
	}

	// �����¿� �� Cell�� ������ �������� �ϳ� ���ؼ� Next Cell ���� �� ���� ���� 
	// ���� Cell �� ������ ArrCurrentCell ������ �ε��� - 1 �� Next Cell �� ���� �� �Լ� ȣ��
	else {
		if (arrNeighborCell.IsEmpty() == true) {
			if (arrCurrentCell.IsEmpty() == true) {
				OnDestinationUnreached.Execute();
			}
			else {
				arrCurrentCell.RemoveAt(arrCurrentCell.Num() - 1);
				if (arrCurrentCell.IsEmpty() != true) {
					nextCell = arrCurrentCell.Last();
					nextCell->SetVisited();
					StartDFS(nextCell);
				}
				else {
					OnDestinationUnreached.Execute();
				}
			}
		}
		else {
			nextCell = arrNeighborCell[FMath::RandRange(0, arrNeighborCell.Num() - 1)];
			nextCell->SetVisited();
			// Delay(0.01)
			co_await UE5Coro::Latent::Seconds(0.1);
			StartDFS(nextCell);
		}
	}
}

void ASearch::StartDijkstra()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StartDijkstra"));
}

void ASearch::StartAstar()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StartAstar"));
}

void ASearch::SetAllCostVisibility()
{
	for (ASearch_Points* arr : arrPoints) {
		arr->SetCostVisibility(true);
	}
}

// ��ó Cell Ž��
void ASearch::FindNeighborCell()
{
	for (ASearch_Points* arr : arrPoints)
	{
		if (arr->isWall != true && arr->isVisited != true) {
			float arrX = arr->GetActorLocation().X;
			float arrY = arr->GetActorLocation().Y;

			float currentX = currentCell->GetActorLocation().X;
			float currentY = currentCell->GetActorLocation().Y;

			// ���� Ȯ��
			if (arrX == (currentX - 100.0) && arrY == currentY) {
				arrNeighborCell.Add(arr);
			}
			// ������ Ȯ��
			else if (arrX == (currentX + 100.0) && arrY == currentY) {
				arrNeighborCell.Add(arr);
			}
			// ���� Ȯ��
			else if (arrX == currentX && arrY == (currentY + 100.0)) {
				arrNeighborCell.Add(arr);
			}
			// �Ʒ��� Ȯ��
			else if (arrX == currentX && arrY == (currentY - 100.0)) {
				arrNeighborCell.Add(arr);
			}
		}
	}
}

