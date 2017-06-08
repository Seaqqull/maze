// Fill out your copyright notice in the Description page of Project Settings.

#include "MDGen.h"
#include "MazeGenerationLogic.h"
#include "Generation.h"
#include "MazeGen.h"
#include "EngineUtils.h"

#include "MeshUtilities.h"
//#include "MeshMergeData.h"
//#include "d:\UnrealEngine-release\Engine\Source\Developer\RawMesh\Public\RawMesh.h"
//#include "d:\UnrealEngine-release\Engine\Source\Developer\HierarchicalLODUtilities\Public\IHierarchicalLODUtilities.h"
//#include "d:\UnrealEngine-release\Engine\Source\Developer\HierarchicalLODUtilities\Public\HierarchicalLODUtilitiesModule.h"

// Sets default values
AMazeGenerationLogic::AMazeGenerationLogic()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

AMazeGenerationLogic::AMazeGenerationLogic(const FObjectInitializer& ObjectInitializer)
{
	WhereToSpawn = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
	PrimaryActorTick.bCanEverTick = true;
}


/*
void AMazeGenerationLogic::CreateMeshComponent(int32 indexMeshe, FVector SpawnLocation, FRotator SpawnRotation, FName ConvertedFString)
{
//UStaticMeshComponent* NewComp = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, ConvertedFString);
//if (NewComp)
//{
//	NewComp->RegisterComponent();
//	NewComp->SetRelativeLocation(SpawnLocation);
//	NewComp->SetRelativeRotation(SpawnRotation);
//	NewComp->AttachTo(RootComponent, NAME_None, EAttachLocation::KeepRelativeOffset);
//	NewComp->SetStaticMesh(StaticMeshToSpawn[indexMeshe]);
//	MySourceActors.Add(/*(AActor*)*\(NewComp));
//}
//UWorld* const World = GetWorld();
//if (World)
//{
//	// Set the spawn parameters
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Owner = this;
//	SpawnParams.Instigator = Instigator;
//	// spawn the pickup
//	//WhatToSpawn = StaticMeshToSpawn[indexMeshe];
//	AGeneration* const SpawnedPickup = World->SpawnActor<AGeneration>(WhatToSpawn[indexMeshe], SpawnLocation, SpawnRotation, SpawnParams);
//}
}
*/

/*void AMazeGenerationLogic::CreateMeshComponent1(int32 indexMeshe, FVector SpawnLocation, FRotator SpawnRotation, FName ConvertedFString)
{
UStaticMeshComponent*  ISMComp = NewObject<UStaticMeshComponent>(this);
ISMComp = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, ConvertedFString);
ISMComp->RegisterComponent();
ISMComp->SetRelativeLocation(SpawnLocation);
ISMComp->SetRelativeRotation(SpawnRotation);
//ISMComp->SetStaticMesh(StaticMeshToSpawn[indexMeshe]);
ISMComp->SetFlags(RF_Transactional);
this->AddInstanceComponent(ISMComp);
}*/




//void AMazeGenerationLogic::RegisterMazeComponent()
//{
//		//maze = new MazeGen();
//		//maze->Dimensioning(SizeMazeX, SizeMazeZ, Sizeroom->Z * 100); //100 - 1 метр
//		//maze->isGenerationMaze = true;
//		//maze->GenerationMaze();
//		
//		room->room->
//		room->Setroom->0, 0, maze->_sizeroom->Y, maze->_sizeroom->Y);
//		
//		
//		FVector SpawnLocation;		
//		FQuat SpawnRotation;
//		
//		FTransform transform;
//		transform.SetLocation(SpawnLocation);
//		transform.SetRotation(SpawnRotation);
//
//		static int name = 0;
//
//		for (int i = 0; i < maze->_sizeMazeX; i++)
//		{
//			for (int j = 0; j < maze->_sizeMazeY; j++)
//			{
//
//				room->shift(maze->_sizeroom->Y, 0);
//			}
//			room->shift(-maze->_sizeroom->Y * maze->_sizeMazeY, maze->_sizeroom->Y);
//		} 
//
//}


void AMazeGenerationLogic::shiftRoomX()
{
	room->shift(maze->_sizeRoomXY, 0);
}

void AMazeGenerationLogic::shiftRoomZ()
{
	room->shift(-maze->_sizeRoomXY * maze->_sizeMazeY, -maze->_sizeRoomXY);
}


void AMazeGenerationLogic::SpawnMeshComponent(int IndexRoom, int IndexOperation, FVector& SpawnLocation, FRotator& SpawnRotation, bool& isTrue)
{
	bitset<4> bits_simple_wall_1, bits_simple_wall_2, bits_simple_wall_3;
	isTrue = true;

	bits_simple_wall_1 = maze->Labirint[IndexRoom];

	if (((IndexRoom + 1) % maze->_sizeMazeY) != 0)
		bits_simple_wall_2 = maze->Labirint[IndexRoom + 1];
	if (IndexRoom < (maze->_sizeMazeX * maze->_sizeMazeY) - maze->_sizeMazeY)
		bits_simple_wall_3 = maze->Labirint[IndexRoom + maze->_sizeMazeY];


	switch (IndexOperation)
	{
	case 0: //t
		if ((bits_simple_wall_1 & bitset<4>(0x8)).any())
		{
			SpawnLocation.X = room->getCenterX();
			SpawnLocation.Y = room->getTop();
		}
		else goto default_lable;
		break;
	case 1: //r
		if ((bits_simple_wall_1 & bitset<4>(0x4)).any())
		{
			SpawnRotation.Yaw = 90;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getCenterY();
		}
		else goto default_lable;
		break;
	case 2: //b
		if ((bits_simple_wall_1 & bitset<4>(0x2)).any())
		{
			SpawnLocation.X = room->getCenterX();
			SpawnLocation.Y = room->getBottom();
		}
		else goto default_lable;
		break;
	case 3: //l	
		if ((bits_simple_wall_1 & (bitset<4>)0x1).any())
		{
			SpawnRotation.Yaw = 90;
			SpawnLocation.X = room->getLeft();
			SpawnLocation.Y = room->getCenterY();
		}
		else goto default_lable;
		break;
	case 4: //f
		SpawnLocation.X = room->getCenterX();
		SpawnLocation.Y = room->getCenterY();
		break;
	case 5:// углы внутри
	{
		if ((bits_simple_wall_1 & bitset<4>(0x2)).any() &
			(bits_simple_wall_1 & bitset<4>(0x4)).any() &
			(!(bits_simple_wall_2 & bitset<4>(0x2)).any()) &
			(!(bits_simple_wall_3 & bitset<4>(0x4)).any())
			)
		{
			SpawnRotation.Yaw = 180;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getBottom();
		}
	    else if ((bits_simple_wall_1 & bitset<4>(0x4)).any() &
			(bits_simple_wall_2 & bitset<4>(0x2)).any() &
			(!(bits_simple_wall_1 & bitset<4>(0x2)).any()) &
			(!(bits_simple_wall_3 & bitset<4>(0x4)).any())
			)
		{
			SpawnRotation.Yaw = 90;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getBottom();
		}
		else if (
			(bits_simple_wall_1 & bitset<4>(0x2)).any() &
			(bits_simple_wall_3 & bitset<4>(0x4)).any() &
			(!(bits_simple_wall_1 & bitset<4>(0x4)).any()) &
			(!(bits_simple_wall_2 & bitset<4>(0x2)).any())
			)
		{
			SpawnRotation.Yaw = -90;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getBottom();
		}
		else if (
			(bits_simple_wall_2 & bitset<4>(0x2)).any() &
			(bits_simple_wall_3 & bitset<4>(0x4)).any() &
			(!(bits_simple_wall_1 & bitset<4>(0x2)).any()) &
			(!(bits_simple_wall_1 & bitset<4>(0x4)).any())
			)
		{
			SpawnRotation.Yaw = 0;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getBottom();
		}
		else goto default_lable;
	}
		break;
	case 6: // углы снаружи
	{
		if (IndexRoom == 0)
		{
			SpawnLocation.X = room->getLeft();
			SpawnLocation.Y = room->getTop();
		}
	    else if (IndexRoom == (maze->_sizeMazeY - 1))
		{
			SpawnRotation.Yaw = 270;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getTop();
		}
		else if ((IndexRoom == (maze->_sizeMazeY * maze->_sizeMazeX) - maze->_sizeMazeY))
		{
			SpawnRotation.Yaw = 90;
			SpawnLocation.X = room->getLeft();
			SpawnLocation.Y = room->getBottom();
		}
		/*else if ((IndexRoom != maze->_exit) & (IndexRoom == (maze->_sizeMazeY * maze->_sizeMazeX) - 1))
		{
			SpawnRotation.Yaw = 180;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getBottom();
		}*/
	    else goto default_lable;
	}
		break;
	case 7: //door
	{
		if (IndexRoom == maze->_entrance)
		{
			SpawnLocation.X = room->getLeft();
			SpawnLocation.Y = room->getCenterY();
		}
		else if (IndexRoom == maze->_exit)
		{
			SpawnRotation.Yaw = 180;
			SpawnLocation.X = room->getRight();
			SpawnLocation.Y = room->getCenterY();
		}
		else goto default_lable;
	}
		break;
	default: 
		default_lable:
		isTrue = false;
	}
}

/*
bool AMazeGenerationLogic::MargeMaze()
{
//For each Actor collected
//for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
//{
//	// Cast the collected Actor to ABatteryPickup
//	AGeneration* const TestBattery = Cast<AGeneration>(CollectedActors[iCollected]);
//}


/*for (TActorIterator<AGeneration> ActorItr(GetWorld()); ActorItr; ++ActorItr)
{
AGeneration *Mesh = *ActorItr;
MySourceActors.Add(Mesh);
}
return false;
}*/


void AMazeGenerationLogic::SuperGenMaze()
{
	maze = new MazeGen(SizeMazeX, SizeMazeY, SizeRoomXZ * 100); // 100 - 1 метр в ue4
	maze->isGenerationMaze = true;
	maze->GenerationMaze(); 
	room = new Room(0, 0, maze->_sizeRoomXY, -maze->_sizeRoomXY);//начальное положение
}

void AMazeGenerationLogic::ClearingMemory_TEST()
{
	maze->ClearMemory();
	delete maze;
	delete room;
}

// Called when the game starts or when spawned
void AMazeGenerationLogic::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMazeGenerationLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

