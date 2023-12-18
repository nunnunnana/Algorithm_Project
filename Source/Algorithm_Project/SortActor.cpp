// Fill out your copyright notice in the Description page of Project Settings.


#include "SortActor.h"

// Sets default values
ASortActor::ASortActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
			int32 LastIndex = arrTarget.Num() - 1;
			for (int32 i = 0; i <= LastIndex; ++i) {
				int32 Index = FMath::RandRange(i, LastIndex);
				if (i != Index) {
					arrTarget.Swap(i, Index);
				}
			}
		}
		SetArrayLocation();
	}
}

// �ʱ�ȭ �Լ�
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

	//for (int i = 0; i < arrTarget.Num() - 1; i++) {
	//	int tmp = i;
	//	for (int j = i + 1; j < arrTarget.Num(); j++) {
	//		if (arrTarget[tmp]->index >= arrTarget[j]->index) {
	//			tmp = j;
	//		}
	//	}
	//	Swap(arrTarget[i], arrTarget[tmp]);
	//}
	//SetArrayLocation();
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
		// Ÿ�̸� ����
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ASortActor::SetSelectionSortColor, 0.1f, true, 0.0f);
	}
}

void ASortActor::SetSelectionSortColor()
{
	if (currentIndex - 1 != tmp) {
		SetArrTargetColor(whiteMat, currentIndex - 1);
	}
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