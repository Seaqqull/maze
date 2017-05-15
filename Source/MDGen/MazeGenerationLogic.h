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
		int SizeMazeZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int SizeRoomXZ;


	UFUNCTION(BlueprintCallable, Category = Spawning)
		int GetWallOrienration(int i, int j);
	UFUNCTION(BlueprintCallable, Category = Spawning)
		void SuperGenMaze();
	UFUNCTION(BlueprintCallable, Category = Spawning)
		void SpawnMeshComponent(int i, int j, FVector& SpawnLocation, FRotator& SpawnRotation, int& OutIndex);
	UFUNCTION(BlueprintCallable, Category = Spawning)
		void shiftRoomX();
	UFUNCTION(BlueprintCallable, Category = Spawning)
		void shiftRoomZ();





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
