// Fill out your copyright notice in the Description page of Project Settings.


#include "SortPawn.h"

// Sets default values
ASortPawn::ASortPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// �������Ʈ Ŭ������ �޾ƿ´�
	static ConstructorHelpers::FClassFinder<UUserWidget> sortWidgetAsset(TEXT("WidgetBlueprint'/Game/Sort/BP_W_Sort.BP_W_Sort_C'"));
	// TSubclassOf ���ø� Ŭ���� ��ü�� �������Ʈ Ŭ������ �־��ش�
	if (sortWidgetAsset.Succeeded()) {
		sortWidgetClass = sortWidgetAsset.Class;
	}


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
}


