// Fill out your copyright notice in the Description page of Project Settings.

#include "MDGen.h"
#include "Generation.h"


AGeneration::AGeneration(const FObjectInitializer& ObjectInitializer)
{
	//The pickup is valid when it is created
	bIsActive = true;

	// Create the root SphereComponent to handle the pickup's collision
	SceneRootComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BaseBoxComponent"));

	// Set the SphereComponent as the root component
	RootComponent = SceneRootComponent;

	//Create the static mesh component 
	GenMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));

	////Turn physics on for the static mesh
	////GenMesh[0]->SetSimulatePhysics(true);

	//Attach the StaticMeshComponent to the root component
	GenMesh->AttachTo(RootComponent);	

}


void AGeneration::OnGenMesh_Implementation()
{
	
}