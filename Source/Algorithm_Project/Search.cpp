// Fill out your copyright notice in the Description page of Project Settings.


#include "Search.h"

// Sets default values
ASearch::ASearch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findGreenMat(TEXT("/Script/Engine.Material'/Game/Asset/Material/M_Base_Green.M_Base_Green'"));
	greenMat = findGreenMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findLightBlueMat(TEXT("/Script/Engine.Material'/Game/Asset/Material/M_Base_LightBlue.M_Base_LightBlue'"));
	lightblueMat = findLightBlueMat.Object;
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
				endPoint = end;
				arrPoints.Add(endPoint);
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
	// 기준이 되는 point 설정
	currentCell = startPoint;
	arrNeighborCell.Empty();
	arrCurrentCell.Add(currentCell);
	// 0.1초 마다 SetSelectionSortColor 함수 실행
	GetWorld()->GetTimerManager().SetTimer(bfsTimer, this, &ASearch::BFS, 0.1f, true, 0.0f);
}

void ASearch::BFS()
{
	if (arrCurrentCell.IsEmpty() != true) {
		// arrCurrentCell의 첫 번째 인덱스를 기준으로 설정하고 첫 번째 인덱스 제거
		currentCell = arrCurrentCell[0];
		arrCurrentCell.RemoveAt(0);

		for (ASearch_Points* arr : arrPoints)
		{
			if (arr->isWall != true && arr->isVisited != true) {
				FindNeighborCell(arr);
			}
		}

		// CellArray에 End point 있는지 확인
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

		// EntPoint에 도달했으면 방문했던 Cell의 색상 변경
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
			// 근처 Cell 탐색해서 담은 배열 초기화
			arrNeighborCell.Empty();
		}
		
	}
	else {
		// EndPoint를 못찾았을 때
		GetWorld()->GetTimerManager().ClearTimer(bfsTimer);
		arrTotalCell.Empty();
		OnDestinationUnreached.Execute();
	}
}

FAsyncCoroutine ASearch::StartDFS(ASearch_Points* point)
{
	// 기준이 되는 point 설정
	if (point != nullptr) {
		currentCell = point;
	}
	else {
		currentCell = startPoint;
	}

	arrNeighborCell.Empty();

	for (ASearch_Points* arr : arrPoints)
	{
		if (arr->isWall != true && arr->isVisited != true) {
			FindNeighborCell(arr);
		}
	}

	// CellArray에 End point 있는지 확인
	for (ASearch_Points* arr : arrNeighborCell)
	{
		if (arr->isEndpoint == true) {
			isfindEndPoint = true;
		}
		else {
			arrCurrentCell.Add(arr);
		}
	}

	// EntPoint에 도달했으면 방문했던 Cell의 색상 변경
	if (isfindEndPoint == true) {
		for (ASearch_Points* arr : arrCurrentCell)
		{
			if (arr->isVisited == true) {
				arr->SetMaterial(greenMat);
			}
		}
		OnDestinationReached.Execute();
	}

	// 상하좌우 중 Cell이 있으면 랜덤으로 하나 정해서 Next Cell 설정 후 색상 변경 
	// 만약 Cell 이 없으면 ArrCurrentCell 마지막 인덱스 - 1 을 Next Cell 로 설정 후 함수 호출
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
			// Delay(0.1)
			co_await UE5Coro::Latent::Seconds(0.1);
			StartDFS(nextCell);
		}
	}
}

void ASearch::StartDijkstra()
{
	// 기준이 되는 point 설정
	currentCell = startPoint;
	arrNeighborCell.Empty();
	arrCurrentCell.Add(currentCell);
	dijkstraCost = 0;
	Research();
}

FAsyncCoroutine ASearch::Research()
{
	for (ASearch_Points* arr : arrCurrentCell) {
		currentCell = arr;
		for (ASearch_Points* arrCell : arrPoints)
		{
			if (arrCell->isWall != true && arrCell->isVisited != true) {
				FindNeighborCell(arrCell);
			}
		}
	}
	// EndPoint를 못찾았을 때
	if (arrNeighborCell.IsEmpty()) {
		arrCurrentCell.Empty();
		arrNeighborCell.Empty();
		OnDestinationUnreached.Execute();
	}
	// CellArray에 End point 있는지 확인
	else {
		dijkstraCost++;
		for (ASearch_Points* arr : arrNeighborCell) {
			if (arr->isEndpoint) {
				isfindEndPoint = true;
				arr->cost = dijkstraCost;
				endPoint = arr;
			}
			else {
				arr->SetVisited();
				arr->cost = dijkstraCost;
				arrCurrentCell.Add(arr);
			}
		}
		// EndPoint 찾았는지 조건 확인
		if (isfindEndPoint == true) {
			currentCell = endPoint;
			ReturnToStartPoint();
		}
		else {
			arrNeighborCell.Empty();
			// Delay(0.2)
			co_await UE5Coro::Latent::Seconds(0.2);
			Research();
		}
	}
}

FAsyncCoroutine ASearch::StartAstar(ASearch_Points* point)
{
	// 기준이 되는 point 설정
	if (point != nullptr) {
		currentCell = point;
	}
	else {
		currentCell = startPoint;
		arrCloseCell.Empty();
		endPoint->g = CalcManhattanDistance(endPoint, startPoint);
	}

	arrNeighborCell.Empty();
	nextCell = nullptr;

	for (ASearch_Points* arr : arrPoints)
	{
		if (arr->isWall != true && arr->isVisited != true) {
			FindNeighborCell(arr);
		}
	}

	// CellArray에 End point 있는지 확인
	for (ASearch_Points* arr : arrNeighborCell)
	{
		if (arr->isEndpoint == true) {
			isfindEndPoint = true;
		}
		else {
			arr->SetVisited();
			arr->h = CalcManhattanDistance(arr, endPoint);
			arr->g = CalcManhattanDistance(arr, startPoint);
			arrCurrentCell.Add(arr);
		}
	}

	// 현재 Cell과 거리 비교해서 Next Cell 설정
	for (ASearch_Points* arr : arrCurrentCell)
	{
		CompareNextCell(arr, currentCell);
	}

	// arrCurrentCell 배열에서 기준 노드 제거 후 배열이 비어있는지 확인
	arrCloseCell.Add(currentCell);
	arrCurrentCell.Remove(currentCell);

	// arrCurrentCell에서 EndPoint를 못찾았을 때
	if (arrCurrentCell.IsEmpty()) {
		arrNeighborCell.Empty();
		nextCell = nullptr;
		OnDestinationUnreached.Execute();
	}
	else {
		// EndPoint를 찾았을 때
		if (isfindEndPoint) {
			arrNeighborCell.Empty();
			currentCell = endPoint;
			OnDestinationReached.Execute();
		}

		// Next Cell이 설정돼었는지 확인 후 없으면 arrCurrentCell 배열에서 Next Cell 설정
		else {
			if (nextCell != nullptr) {
				// Delay(0.2)
				co_await UE5Coro::Latent::Seconds(0.2);
				nextCell->SetMaterial(lightblueMat);
				StartAstar(nextCell);
			}
			else {
				for (int index = 0; index != arrCurrentCell.Num(); index++)
				{
					if (index == 0) {
						nextCell = arrCurrentCell[0];
					}
					else {
						CompareNextCell(arrCurrentCell[index], nextCell);
					}
				}
				// Delay(0.2)
				co_await UE5Coro::Latent::Seconds(0.2);
				nextCell->SetMaterial(lightblueMat);
				StartAstar(nextCell);
			}
		}
	}
}

// Activate dijkstra cost
void ASearch::ActivateDijkstra()
{
	for (ASearch_Points* arr : arrPoints) {
		arr->SetDijkstra();
	}
}

// Activate a star distance value
void ASearch::ActivateAStar()
{
	for (ASearch_Points* arr : arrPoints) {
		arr->SetAStar();
	}
}

// 근처 Cell 탐색
void ASearch::FindNeighborCell(ASearch_Points* point)
{
	float pointX = point->GetActorLocation().X;
	float pointY = point->GetActorLocation().Y;

	float currentX = currentCell->GetActorLocation().X;
	float currentY = currentCell->GetActorLocation().Y;

	// 왼쪽 확인
	if (pointX == (currentX - 100.0) && pointY == currentY) {
		arrNeighborCell.Add(point);
	}
	// 오른쪽 확인
	else if (pointX == (currentX + 100.0) && pointY == currentY) {
		arrNeighborCell.Add(point);
	}
	// 위쪽 확인
	else if (pointX == currentX && pointY == (currentY + 100.0)) {
		arrNeighborCell.Add(point);
	}
	// 아래쪽 확인
	else if (pointX == currentX && pointY == (currentY - 100.0)) {
		arrNeighborCell.Add(point);
	}
}

// 시작지점으로 돌아가기
void ASearch::ReturnToStartPoint()
{
	for (ASearch_Points* arr : arrPoints)
	{
		// Visited 조건 확인 안하고 근처 Cell 탐색
		if (arr->isWall != true) {
			FindNeighborCell(arr);
		}
	}
	for (ASearch_Points* arr : arrNeighborCell)
	{
		if (arr->cost == (dijkstraCost - 1)) {
			currentCell = arr;
		}
	}
	// 초기 지점으로 돌아왔으면 탐색 성공 표시
	if (dijkstraCost == 1) {
		arrCurrentCell.Empty();
		arrNeighborCell.Empty();
		OnDestinationReached.Execute();
	}
	// cost에 -1하면서 색상 변경 후 함수 호출
	else {
		dijkstraCost--;
		arrNeighborCell.Empty();
		currentCell->SetMaterial(greenMat);
		ReturnToStartPoint();
	}
}

// 두 지점의 맨해튼 거리 계산
float ASearch::CalcManhattanDistance(ASearch_Points* currentPoint, ASearch_Points* targetPoint)
{
	float result = 0.0f;
	float currentX = currentPoint->GetActorLocation().X;
	float currentY = currentPoint->GetActorLocation().Y;

	float targetX = targetPoint->GetActorLocation().X;
	float targetY = targetPoint->GetActorLocation().Y;

	result = (currentX - targetX) + (currentY - targetY);

	return abs(result);
}

// 두 Cell의 거리 비교 후 Next Cell 설정
void ASearch::CompareNextCell(ASearch_Points* targetPoint, ASearch_Points* currentPoint)
{
	if ((targetPoint->g + targetPoint->h) > (currentPoint->g + currentPoint->h)) {
		nextCell = targetPoint;
	}
	else if ((targetPoint->g + targetPoint->h) == (currentPoint->g + currentPoint->h)) {
		if (targetPoint->g > currentPoint->g) {
			nextCell = targetPoint;
		}
	}
}
