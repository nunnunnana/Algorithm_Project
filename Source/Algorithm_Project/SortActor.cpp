// Fill out your copyright notice in the Description page of Project Settings.


#include "SortActor.h"

// Sets default values
ASortActor::ASortActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// materialinstance 레퍼런스 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findwhiteMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Asset/Material/M_Base_White.M_Base_White'"));
	whiteMat = findwhiteMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findyellowMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Asset/Material/M_Base_Yellow.M_Base_Yellow'"));
	yellowtMat = findyellowMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findredMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Asset/Material/M_Base_Red.M_Base_Red'"));
	redMat = findredMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findblueMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Asset/Material/M_Base_Blue.M_Base_Blue'"));
	blueMat = findblueMat.Object;

}

// Called when the game starts or when spawned
void ASortActor::BeginPlay()
{
	Super::BeginPlay();

	// size 값 만큼 메시 Spawn
	for (int i = 0; i < size; i++) {
		if (currentTarget == nullptr) {
			SpawnActor(this, i);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("this"));
		}
		// 기존에 생성한 액터가 있을 경우 위치 이동 후 생성
		else {
			SpawnActor(currentTarget, i);
		}
	}
}

// Called every frame
void ASortActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 액터 생성 함수
void ASortActor::SpawnActor(AActor* targetActor, int actorIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), actorIndex));
	FVector currentLocation = targetActor->GetActorLocation();
	currentLocation.Y = actorIndex * 100;
	FRotator rotation(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	ASortActorMesh* target = (ASortActorMesh*)GetWorld()->SpawnActor<ASortActorMesh>(ASortActorMesh::StaticClass(), currentLocation, rotation, SpawnParams);
	currentTarget = target;
	currentTarget->index = actorIndex;
	arrTarget.Add(currentTarget);
}

// 배열의 인덱스 위치와 Location 값 동기화 함수
void ASortActor::SetArrayLocation()
{
	for (int i = 0; i < arrTarget.Num(); i++) {
		FVector currentLocation = arrTarget[i]->GetActorLocation();
		currentLocation.Y = i * 100;
		arrTarget[i]->SetActorLocation(currentLocation);
	}
}

// arrTarget 배열 셔플 함수
void ASortActor::ShuffleArray()
{
	if (IsSorting == false) {
		Init();
		if (arrTarget.Num() > 0) {
			int lastIndex = arrTarget.Num() - 1;
			for (int i = 0; i <= lastIndex; ++i) {
				int Index = FMath::RandRange(i, lastIndex);
				if (i != Index) {
					arrTarget.Swap(i, Index);
				}
			}
		}
		SetArrayLocation();
	}
}

// 색상 초기화 함수
void ASortActor::Init()
{
	for (int i = 0; i < arrTarget.Num(); i++) {
		SetArrTargetColor(whiteMat, i);
	}
}

// 색상 설정 함수
void ASortActor::SetArrTargetColor(UMaterialInstance* material, int targetIndex)
{
	arrTarget[targetIndex]->SetActorColor(material);
}

// 정렬 알고리즘 시작 함수
void ASortActor::SelectionSort()
{
	if (IsSorting == false) {
		Init();
		index = 0;
		StartSelectionSort();
		IsSorting = true;
	}
}

// 선택 정렬 함수
void ASortActor::StartSelectionSort()
{
	if (index >= arrTarget.Num() - 1) {
		SetArrTargetColor(yellowtMat, index);
		IsSorting = false;
	}
	else {
		tmp = index;
		SetArrTargetColor(redMat, tmp);
		currentIndex = index + 1;
		// 0.02초 마다 SetSelectionSortColor 함수 실행
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASortActor::SetSelectionSortColor, 0.02f, true, 0.0f);
	}
}

// 가장 낮은 Index 찾은 후 색상 변경
void ASortActor::SetSelectionSortColor()
{
	if (currentIndex - 1 != tmp) {
		SetArrTargetColor(whiteMat, currentIndex - 1);
	}
	// index와 tmp의 arrTarget 배열 원소 위치 변경 후 노란색으로 설정
	if (currentIndex >= arrTarget.Num()) {
		// 타이머 초기화
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		arrTarget.Swap(index, tmp);
		SetArrTargetColor(yellowtMat, index);
		SetArrayLocation();
		index++;
		StartSelectionSort();
	}
	else {
		// 가장 낮은 Index를 가진 원소의 색상을 빨간색으로 설정
		if (arrTarget[tmp]->index >= arrTarget[currentIndex]->index) {
			SetArrTargetColor(whiteMat, tmp);
			tmp = currentIndex;
			SetArrTargetColor(redMat, tmp);
		}
		else {
			SetArrTargetColor(blueMat, currentIndex);
		}
		currentIndex++;
	}
}