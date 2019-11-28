// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "Generation.generated.h"

UCLASS()
class MDGEN_API AGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneration() { }

	AGeneration(const FObjectInitializer& ObjectInitializer);

	/** True when the pickup is able to be picked up, false if something deactivates the pickup. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeGeneration)
		bool bIsActive;

	/** Simple collision primitive to use as the root component. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MazeGen)
		UBoxComponent* SceneRootComponent;

	/** StaticMeshComponent to represent the pickup in the level */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MazeGen)
		  UStaticMeshComponent*  GenMesh;

	
	
	


	/** Function to call when the Pickup is collected */
	UFUNCTION(BlueprintNativeEvent)
		void OnGenMesh();

 
};
