// Fill out your copyright notice in the Description page of Project Settings.


#include "SortActor.h"

// Sets default values
ASortActor::ASortActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Asset/Material/M_Base_White.M_Base_White'"));
	currentMat = findMat.Object;
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
	Init();
	if (arrTarget.Num() > 0){
		int32 LastIndex = arrTarget.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i){
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index){
				arrTarget.Swap(i, Index);
			}
		}
	}
	SetArrayLocation();
}

// 초기화 함수
void ASortActor::Init()
{
	for (int i = 0; i < arrTarget.Num(); i++) {
		SetArrTargetColor(currentMat, i);
	}
}

// 색상 설정 함수
void ASortActor::SetArrTargetColor(UMaterialInstance* material, int targetIndex)
{
	arrTarget[targetIndex]->SetActorColor(material);

}

// 선택 정렬 함수
void ASortActor::SelectionSort()
{
	Init();
	for (int i = 0; i < arrTarget.Num() - 1; i++) {
		int tmp = i;
		for (int j = i + 1; j < arrTarget.Num(); j++) {
			if (arrTarget[tmp]->index >= arrTarget[j]->index) {
				tmp = j;
			}
		}
		Swap(arrTarget[i], arrTarget[tmp]);
	}
	SetArrayLocation();
}