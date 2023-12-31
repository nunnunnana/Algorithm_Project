// Fill out your copyright notice in the Description page of Project Settings.


#include "SortPawn.h"

// Sets default values
ASortPawn::ASortPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// 블루프린트 클래스를 받아온다
	static ConstructorHelpers::FClassFinder<UUserWidget> sortWidgetAsset(TEXT("WidgetBlueprint'/Game/Sort/BP_W_Sort.BP_W_Sort_C'"));
	// TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어준다
	if (sortWidgetAsset.Succeeded()) {
		sortWidgetClass = sortWidgetAsset.Class;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> findMat(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Asset/Material/M_Base_Red.M_Base_Red'"));
	currentMat = findMat.Object;

}

// Called when the game starts or when spawned
void ASortPawn::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(sortWidgetClass))
	{
		sortWidget = Cast<UW_Sort>(CreateWidget(GetWorld(), sortWidgetClass));

		if (IsValid(sortWidget))
		{
			sortWidget->AddToViewport();
		}
	}

}

// Called every frame
void ASortPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASortPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Z", IE_Pressed, this, &ASortPawn::Z);
	PlayerInputComponent->BindAction("X", IE_Pressed, this, &ASortPawn::X);
	PlayerInputComponent->BindAction("C", IE_Pressed, this, &ASortPawn::C);
}

void ASortPawn::Z()
{
	sortActor->ShuffleArray();
}

void ASortPawn::X()
{
	sortActor->QuickSort();
}

void ASortPawn::C()
{

}