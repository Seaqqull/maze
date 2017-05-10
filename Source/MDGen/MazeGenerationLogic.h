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
	/** brick to spawn */
	//UPROPERTY(EditAnywhere, Category = Spawning)
	//TSubclassOf<class AGeneration> WhatToSpawn;
		//TSubclassOf<class AGeneration> WhatToSpawn;
	
	

	UPROPERTY(EditAnywhere, Category = Spawning)
		TArray<UStaticMesh*> StaticMeshToSpawn;

	/** BoxComponent to specify the spawning area within the level */
	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	UBoxComponent* WhereToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		TArray<FVector> StaticMeshLocationCorrect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int SizeMazeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int SizeMazeZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int SizeRoomXZ;

	UFUNCTION(BlueprintPure, Category = Spawning)
		bool SuperGenMaze();


private:
	void RegisterMazeComponent();
	void CreateMeshComponent(int32 indexMeshe, FVector SpawnLocation, FRotator SpawnRotation, FName ConvertedFString);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//AGeneration* const Spawning(int indexBrick, FVector SpawnLocation, FRotator SpawnRotation, FActorSpawnParameters SpawnParams);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
