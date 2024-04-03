// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortActorMesh.h"
#include <coroutine>
#include "Kismet/KismetArrayLibrary.h"
#include "Components/TimeLineComponent.h"
#include "SortActor.generated.h"

namespace co = std;

UCLASS()
class ALGORITHM_PROJECT_API ASortActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASortActor();

	UPROPERTY(EditAnyWhere)
	int size;

	struct promise_type
	{
		ASortActor get_return_object() 
		{
			return ASortActor{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() { return std::suspend_always{}; }
		void unhandled_exception() { std::exit(1); }
	};

	std::coroutine_handle<promise_type> co_handler;

	ASortActor(std::coroutine_handle<promise_type> handler) : co_handler(handler) { }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int index;
	int currentIndex;
	int tmp;
	int bstart;
	int start;
	int end;
	bool IsSorting;

	UPROPERTY()
	ASortActorMesh* currentTarget;

	UPROPERTY()
	ASortActorMesh* arget;

	UPROPERTY()
	UMaterialInstance* whiteMat;

	UPROPERTY()
	UMaterialInstance* yellowtMat;

	UPROPERTY()
	UMaterialInstance* redMat;

	UPROPERTY()
	UMaterialInstance* blueMat;

	UPROPERTY()
	TArray<ASortActorMesh*> arrTarget;

	FTimerHandle Timer;
	UFUNCTION()
	void SetSelectionSortColor();

	UFUNCTION()
	void SetInjectionSortColor();

	UFUNCTION()
	void SetBubbleSortColor();

	UFUNCTION()
	void SetMergeSortColor(TArray<ASortActorMesh*>& v, int s, int e, int m);

	UFUNCTION()
	void SetQuickSortColor(TArray<ASortActorMesh*>& arr, int s, int e, int bs, int be);

	UFUNCTION()
	void QuickTest();

	UFUNCTION()
	void QuickTest_1();

	UFUNCTION()
	void Merge_Test(TArray<ASortActorMesh*>& v, int s);

	UFUNCTION()
	void SpawnActor(AActor* targetActor, int actorIndex);

	UFUNCTION()
	void SetArrayLocation();

	UFUNCTION()
	void Init();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ShuffleArray();

	UFUNCTION()
	void SetArrTargetColor(UMaterialInstance* material, int targetIndex);

	UFUNCTION()
	void SelectionSort();

	UFUNCTION()
	void StartSelectionSort();

	UFUNCTION()
	void InjectionSort();

	UFUNCTION()
	void StartInjectionSort();

	UFUNCTION()
	void BubbleSort();

	UFUNCTION()
	void StartBubbleSort(); 

	UFUNCTION()
	void MergeSort();

	UFUNCTION()
	void StartMergeSort(TArray<ASortActorMesh*>& arr, int firstIndex, int lastIndex);

	UFUNCTION()
	void QuickSort();

	UFUNCTION()
	void StartQuickSort(TArray<ASortActorMesh*>& arr, int firstIndex, int lastIndex);

	UFUNCTION()
	ASortActor Task() {


		//co_await std::suspend_always{};
	}

	constexpr void await_suspend(co::coroutine_handle<>) const noexcept {}

	struct generator {
		struct promise_type;
		using handle = std::coroutine_handle<promise_type>;
		struct promise_type {
			int current_value;
			static auto get_return_object_on_allocation_failure() { return generator{ nullptr }; }
			auto get_return_object() { return generator{ handle::from_promise(*this) }; }
			auto initial_suspend() { return std::suspend_always{}; }
			auto final_suspend() noexcept { return std::suspend_always{}; }
			void unhandled_exception() { std::terminate(); }
			void return_void() {}
			auto yield_value(int value) {
				current_value = value;
				return std::suspend_always{};
			}
		};
		bool move_next() { return coro ? (coro.resume(), !coro.done()) : false; }
		int current_value() { return coro.promise().current_value; }
		generator(generator const&) = delete;
		generator(generator&& rhs) : coro(rhs.coro) { rhs.coro = nullptr; }
		~generator() { if (coro) coro.destroy(); }
	private:
		generator(handle h) : coro(h) {}
		handle coro;
	};

};
