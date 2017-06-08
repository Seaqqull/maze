// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MazeGenerationLogic.generated.h"


UCLASS()
class MDGEN_API AMazeGenerationLogic : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMazeGenerationLogic();
	AMazeGenerationLogic(const FObjectInitializer& ObjectInitializer);

	/**/
	//MazeGen maze;
	class MazeGen* maze;
	class Room* room;

	/** brick to spawn */
	/*UPROPERTY(EditAnywhere, Category = Spawning)
	TArray<TSubclassOf<class AGeneration>> WhatToSpawn;*/

	/** BoxComponent to specify the spawning area within the level */
	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
		UBoxComponent* WhereToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int SizeMazeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int SizeMazeY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int SizeRoomXZ;

	UFUNCTION(BlueprintCallable, Category = Spawning)
		void SuperGenMaze();
	UFUNCTION(BlueprintCallable, Category = Spawning)
		/*
			IndexOperation = 0 -> spawn top wall
			IndexOperation = 1 -> spawn right wall
			IndexOperation = 2 -> spawn bottom wall
			IndexOperation = 3 -> spawn left wall
			IndexOperation = 4 -> spawn floor wall
			IndexOperation = 5 -> spawn ñorners inside wall
			IndexOperation = 6 -> spawn ñorners outside wall
			IndexOperation = 7 -> spawn doors (entrance or exit)
			--------------------------------------------
			IndexRoom - counter [0 ... count rooms]
			--------------------------------------------
			isTrue - flag vupolneniya
			--------------------------------------------
		*/
		void SpawnMeshComponent(int IndexRoom, int IndexOperation, /*UPARAM(ref) int& bits_angle_wall,*/ FVector& SpawnLocation, FRotator& SpawnRotation, bool& isTrue);
	UFUNCTION(BlueprintCallable, Category = Spawning)
		void shiftRoomX();
	UFUNCTION(BlueprintCallable, Category = Spawning)
		void shiftRoomZ();
	UFUNCTION(BlueprintCallable, Category = Spawning)
		void ClearingMemory_TEST();





private:

	//void CreateMeshComponent(int32 indexMeshe, FVector SpawnLocation, FRotator SpawnRotation, FName ConvertedFString);
	//void CreateMeshComponent1(int32 indexMeshe, FVector SpawnLocation, FRotator SpawnRotation, FName ConvertedFString);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
