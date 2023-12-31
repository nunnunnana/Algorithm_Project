// Fill out your copyright notice in the Description page of Project Settings.


#include "SortActor.h"
#include "Engine/World.h"
#include "TimerManager.h"

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

// 정렬 알고리즘 시작 함수
void ASortActor::InjectionSort()
{
	if (IsSorting == false) {
		Init();
		index = 1;
		StartInjectionSort();
		IsSorting = true;
	}
}

// 선택 정렬 함수
void ASortActor::StartInjectionSort()
{
	if (index > arrTarget.Num() - 1) {
		IsSorting = false;
	}
	else {
		tmp = arrTarget[index]->index;
		currentIndex = index - 1;
		// 0.02초 마다 SetInjectionSortColor 함수 실행
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASortActor::SetInjectionSortColor, 0.02f, true, 0.0f);
	}
}

// 원소 비교 후 색상 설정
void ASortActor::SetInjectionSortColor()
{
	if (currentIndex >= 0 && tmp < arrTarget[currentIndex]->index) {
		SetArrTargetColor(whiteMat, currentIndex);
		SetArrTargetColor(blueMat, currentIndex + 1);
		arrTarget.Swap(currentIndex, currentIndex + 1);
		currentIndex--;
		SetArrayLocation();
	}
	else {
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		arrTarget[currentIndex + 1]->index = tmp;
		SetArrTargetColor(whiteMat, currentIndex + 1);
		index++;
		StartInjectionSort();
	}
}

// 버블 정렬 함수
void ASortActor::BubbleSort()
{
	if (IsSorting == false) {
		Init();
		index = 0;
		currentIndex = 1;
		StartBubbleSort();
		IsSorting = true;
	}
}

// 선택 정렬 함수
void ASortActor::StartBubbleSort()
{
	if (index >= arrTarget.Num() - 1) {
		IsSorting = false;
	}
	else {
		if (currentIndex >= arrTarget.Num() - index) {
			index++;
			currentIndex = 1;
			StartBubbleSort();
		}
		else {
			tmp = currentIndex - 1;
			// Tmp가 CurrentIndex보다 크면 스왑 후 빨간색으로 변경, 스왑 안하면 파란색으로 변경
			if (arrTarget[tmp]->index > arrTarget[currentIndex]->index) {
				arrTarget.Swap(currentIndex, tmp);
				SetArrTargetColor(redMat, currentIndex);
				SetArrTargetColor(redMat, tmp);
			}
			else {
				SetArrTargetColor(blueMat, currentIndex);
				SetArrTargetColor(blueMat, tmp);
			}
			// 0.02초 뒤에 SetBubbleSortColor 함수 실행
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASortActor::SetBubbleSortColor, 0.02f, false, 0.0f);
		}
	}
}

// 기본색으로 변경 후 다음 원소 비교 시작
void ASortActor::SetBubbleSortColor()
{
	SetArrTargetColor(whiteMat, currentIndex);
	SetArrTargetColor(whiteMat, tmp);
	currentIndex++;
	StartBubbleSort();
	SetArrayLocation();
}

// 합병 정렬 함수
void ASortActor::MergeSort()
{
	StartMergeSort(arrTarget, 0, arrTarget.Num() - 1);
}

// 선택 정렬 함수
void ASortActor::StartMergeSort(TArray<ASortActorMesh*>& arr, int firstIndex, int lastIndex)
{
	if (firstIndex < lastIndex) {
		int m = (firstIndex + lastIndex) / 2;
		StartMergeSort(arr, firstIndex, m); 
		StartMergeSort(arr, m + 1, lastIndex);
		SetMergeSortColor(arr, firstIndex, lastIndex, m);

		//FTimerDelegate TimerDel;
		//FTimerHandle TimerHandle;

		//TimerDel.BindUFunction(this, FName("SetMergeSortColor"), arr, firstIndex, lastIndex, m);
		////Calling MyUsefulFunction after 5 seconds without looping
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.5f, false);

		SetArrayLocation();
	}
}

// 기본색으로 변경 후 다음 원소 비교 시작
void ASortActor::SetMergeSortColor(TArray<ASortActorMesh*>& v, int s, int e, int m)
{
	TArray<ASortActorMesh*> ret;
	int i = s, j = m + 1, copy = 0;

	while (i <= m && j <= e) {
		if (v[i]->index < v[j]->index)
			ret.Add(v[i++]);
		else if (v[i]->index > v[j]->index)
			ret.Add(v[j++]);
	}

	while (i <= m)
		ret.Add(v[i++]);
	while (j <= e)
		ret.Add(v[j++]);
	
	for (int k = s; k <= e; k++) {

		v[k] = ret[copy++];
		//FTimerDelegate TimerDel;
		//FTimerHandle TimerHandle;

		//TimerDel.BindUFunction(this, FName("Merge_Test"), ret, copy);
		////Calling MyUsefulFunction after 5 seconds without looping
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.5f, false);
	}
}

// 기본색으로 변경 후 다음 원소 비교 시작
void ASortActor::Merge_Test(TArray<ASortActorMesh*>& v, int s)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("this"));
}

// 퀵 정렬 함수
void ASortActor::QuickSort()
{
	StartQuickSort(arrTarget, 0, arrTarget.Num() - 1);
}

// 퀵 정렬 함수
void ASortActor::StartQuickSort(TArray<ASortActorMesh*>& arr, int s, int e)
{
	int pivot = arr[s]->index;
	int bs = s, be = e;
	while (s < e) {
		while (pivot <= arr[e]->index && s < e) {
			e--;
		}
		if (s > e) {
			break;
		}
		while (pivot >= arr[s]->index && s < e) {
			s++;
		}
		if (s > e) {
			break;
		}
		SetArrTargetColor(blueMat, s);
		SetArrTargetColor(blueMat, e);
		Swap(arr[s], arr[e]);

		FTimerHandle GravityTimerHandle_0;
		float GravityTime_0 = 0.2f;

		GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle_0, FTimerDelegate::CreateLambda([&, s, e]()
			{
				SetArrTargetColor(whiteMat, s);
				SetArrTargetColor(whiteMat, e);

				GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle_0);
			}), GravityTime_0, false);

	}

	SetArrTargetColor(blueMat, bs);
	SetArrTargetColor(blueMat, s);
	Swap(arr[bs], arr[s]);

	FTimerHandle GravityTimerHandle;
	float GravityTime = 0.2f;

	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&, bs, be, s, e]()
		{
			SetArrTargetColor(whiteMat, bs);
			SetArrTargetColor(whiteMat, s);

			if (bs < s) {
				StartQuickSort(arrTarget, bs, s - 1);
			}
			if (be > e) {
				StartQuickSort(arrTarget, s + 1, be);
			}
			SetArrayLocation();
			GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);
		}), GravityTime, false);

	//FTimerHandle delayTimerHandle;
	//float delayTime = 0.2f;

	//GetWorld()->GetTimerManager().SetTimer(delayTimerHandle, FTimerDelegate::CreateLambda([&, bs, be, s, e]()
	//	{
	//		SetArrTargetColor(whiteMat, bs);
	//		SetArrTargetColor(whiteMat, s);
	//		if (bs < s) {
	//			StartQuickSort(arrTarget, bs, s - 1);
	//		}
	//		if (be > e) {
	//			StartQuickSort(arrTarget, s + 1, be);
	//		}
	//		SetArrayLocation();
	//	}), delayTime, false);
}

// 기본색으로 변경 후 다음 원소 비교 시작
void ASortActor::QuickTest()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("this"));
	SetArrTargetColor(whiteMat, bstart);
	SetArrTargetColor(whiteMat, start);
	StartQuickSort(arrTarget, bstart, start - 1);
	SetArrayLocation();
}


// 기본색으로 변경 후 다음 원소 비교 시작
void ASortActor::QuickTest_1()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("this"));
	StartQuickSort(arrTarget, currentIndex + 1, tmp);
	SetArrayLocation();
}

// 기본색으로 변경 후 다음 원소 비교 시작
void ASortActor::SetQuickSortColor(TArray<ASortActorMesh*>& arr, int s, int e, int bs, int be)
{
	if (bs < s) {
		StartQuickSort(arr, bs, s - 1);
	}
	else if (be > e) {
		StartQuickSort(arr, s + 1, be);
	}
	SetArrayLocation();
}
