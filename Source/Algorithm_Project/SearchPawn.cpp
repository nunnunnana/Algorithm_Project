// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchPawn.h"

// Sets default values
ASearchPawn::ASearchPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// �������Ʈ Ŭ������ �޾ƿ´�
	static ConstructorHelpers::FClassFinder<UUserWidget> searchWidgetAsset(TEXT("WidgetBlueprint'/Game/Search/BP_W_Search.BP_W_Search_C'"));
	// TSubclassOf ���ø� Ŭ���� ��ü�� �������Ʈ Ŭ������ �־��ش�
	if (searchWidgetAsset.Succeeded()) {
		searchWidgetClass = searchWidgetAsset.Class;
	}

}

// Called when the game starts or when spawned
void ASearchPawn::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(searchWidgetClass))
	{
		searchWidget = Cast<UW_Search>(CreateWidget(GetWorld(), searchWidgetClass));

		if (IsValid(searchWidget))
		{
			searchWidget->AddToViewport();
		}
	}
	
}

// Called every frame
void ASearchPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASearchPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
