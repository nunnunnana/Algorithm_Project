// Fill out your copyright notice in the Description page of Project Settings.


#include "SortActor.h"

// Sets default values
ASortActor::ASortActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// materialinstance ���۷��� ����
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

	// size �� ��ŭ �޽� Spawn
	for (int i = 0; i < size; i++) {
		if (currentTarget == nullptr) {
			SpawnActor(this, i);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("this"));
		}
		// ������ ������ ���Ͱ� ���� ��� ��ġ �̵� �� ����
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

// ���� ���� �Լ�
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

// �迭�� �ε��� ��ġ�� Location �� ����ȭ �Լ�
void ASortActor::SetArrayLocation()
{
	for (int i = 0; i < arrTarget.Num(); i++) {
		FVector currentLocation = arrTarget[i]->GetActorLocation();
		currentLocation.Y = i * 100;
		arrTarget[i]->SetActorLocation(currentLocation);
	}
}

// arrTarget �迭 ���� �Լ�
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

// ���� �ʱ�ȭ �Լ�
void ASortActor::Init()
{
	for (int i = 0; i < arrTarget.Num(); i++) {
		SetArrTargetColor(whiteMat, i);
	}
}

// ���� ���� �Լ�
void ASortActor::SetArrTargetColor(UMaterialInstance* material, int targetIndex)
{
	arrTarget[targetIndex]->SetActorColor(material);
}

// ���� �˰��� ���� �Լ�
void ASortActor::SelectionSort()
{
	if (IsSorting == false) {
		Init();
		index = 0;
		StartSelectionSort();
		IsSorting = true;
	}
}

// ���� ���� �Լ�
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
		// 0.02�� ���� SetSelectionSortColor �Լ� ����
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASortActor::SetSelectionSortColor, 0.02f, true, 0.0f);
	}
}

// ���� ���� Index ã�� �� ���� ����
void ASortActor::SetSelectionSortColor()
{
	if (currentIndex - 1 != tmp) {
		SetArrTargetColor(whiteMat, currentIndex - 1);
	}
	// index�� tmp�� arrTarget �迭 ���� ��ġ ���� �� ��������� ����
	if (currentIndex >= arrTarget.Num()) {
		// Ÿ�̸� �ʱ�ȭ
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		arrTarget.Swap(index, tmp);
		SetArrTargetColor(yellowtMat, index);
		SetArrayLocation();
		index++;
		StartSelectionSort();
	}
	else {
		// ���� ���� Index�� ���� ������ ������ ���������� ����
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

// ���� �˰��� ���� �Լ�
void ASortActor::InjectionSort()
{
	if (IsSorting == false) {
		Init();
		index = 1;
		StartInjectionSort();
		IsSorting = true;
	}
}

// ���� ���� �Լ�
void ASortActor::StartInjectionSort()
{
	if (index > arrTarget.Num() - 1) {
		IsSorting = false;
	}
	else {
		tmp = arrTarget[index]->index;
		currentIndex = index - 1;
		// 0.02�� ���� SetInjectionSortColor �Լ� ����
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASortActor::SetInjectionSortColor, 0.02f, true, 0.0f);
	}
}

// ���� �� �� ���� ����
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

// ���� ���� �Լ�
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

// ���� ���� �Լ�
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
			// Tmp�� CurrentIndex���� ũ�� ���� �� ���������� ����, ���� ���ϸ� �Ķ������� ����
			if (arrTarget[tmp]->index > arrTarget[currentIndex]->index) {
				arrTarget.Swap(currentIndex, tmp);
				SetArrTargetColor(redMat, currentIndex);
				SetArrTargetColor(redMat, tmp);
			}
			else {
				SetArrTargetColor(blueMat, currentIndex);
				SetArrTargetColor(blueMat, tmp);
			}
			// 0.02�� ���� SetBubbleSortColor �Լ� ����
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASortActor::SetBubbleSortColor, 0.02f, false, 0.0f);
		}
	}
}

// �⺻������ ���� �� ���� ���� �� ����
void ASortActor::SetBubbleSortColor()
{
	SetArrTargetColor(whiteMat, currentIndex);
	SetArrTargetColor(whiteMat, tmp);
	currentIndex++;
	StartBubbleSort();
	SetArrayLocation();
}

// �պ� ���� �Լ�
void ASortActor::MergeSort()
{
	StartMergeSort(arrTarget, 0, arrTarget.Num() - 1);
}

// ���� ���� �Լ�
void ASortActor::StartMergeSort(TArray<ASortActorMesh*>& arr, int firstIndex, int lastIndex)
{
	if (firstIndex < lastIndex) {
		int m = (firstIndex + lastIndex) / 2;
		StartMergeSort(arr, firstIndex, m);
		StartMergeSort(arr, m + 1, lastIndex);
		SetArrayLocation();
	}
}

// �⺻������ ���� �� ���� ���� �� ����
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
	}
	SetArrayLocation();
}