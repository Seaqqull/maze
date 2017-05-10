// Fill out your copyright notice in the Description page of Project Settings.

#include "MDGen.h"
#include "MazeGenerationLogic.h"
#include "Generation.h"
#include "MazeGen.h"


// Sets default values
AMazeGenerationLogic::AMazeGenerationLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMazeGenerationLogic::AMazeGenerationLogic(const FObjectInitializer& ObjectInitializer)
{

	// Create the simple StaticMeshComponent to represent the pickup in the level 
	WhereToSpawn = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));
	
	// Set the StaticMeshComponent as the root component
	RootComponent = WhereToSpawn;

	//SuperGenMaze();


	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMazeGenerationLogic::CreateMeshComponent(int32 indexMeshe, FVector SpawnLocation, FRotator SpawnRotation, FName ConvertedFString)
{
	UStaticMeshComponent* NewComp = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, ConvertedFString);
	if (NewComp)
	{
		NewComp->RegisterComponent();
		NewComp->SetRelativeLocation(SpawnLocation);
		NewComp->SetRelativeRotation(SpawnRotation);
		NewComp->AttachTo(RootComponent, NAME_None, EAttachLocation::KeepRelativeOffset);
		NewComp->SetStaticMesh(StaticMeshToSpawn[indexMeshe]);
	}
}


void AMazeGenerationLogic::RegisterMazeComponent()
{
		maze = new MazeGen();
		maze->Dimensioning(SizeMazeX, SizeMazeZ, SizeRoomXZ * 100); //100 - 1 метр
		maze->isGenerationMaze = true;
		maze->GenerationMaze();
		
		Room room;
		room.SetRoom(0, 0, maze->_sizeRoomXY, maze->_sizeRoomXY);
		
		FString TheString;
		FName ConvertedFString;	
		FVector SpawnLocation;		
		FRotator SpawnRotation;

		static int name = 0;

		for (int i = 0; i < maze->_sizeMazeX; i++)
		{
			for (int j = 0; j < maze->_sizeMazeY; j++)
			{
				if (maze->Labirint[i][j] > 0 || maze->Labirint[i][j] == -1)	{	}
				else
				{
					TheString = FString::FromInt(name++);
					ConvertedFString = FName(*TheString);
					
					SpawnLocation.Z = 0.0f;
					SpawnRotation.Yaw = 0.0f;
					SpawnRotation.Pitch = 0.0f;
					SpawnRotation.Roll = 0.0f;

					
					switch (maze->GetWall(i, j))
					{
						case 1: //| 90 top		
						{
							//pDC->FillRect(rect, new CBrush(RGB(240, 248, 255)));
							SpawnLocation.X = 1.0f * room.getCenterX();				
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 90.0f + 0.000001f;
							CreateMeshComponent(0, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 2: // |
						{
							//pDC->FillRect(rect, new CBrush(RGB(250, 235, 215)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							CreateMeshComponent(0, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 3: //Г 270 top
						{
							//pDC->FillRect(rect, new CBrush(RGB(0, 255, 255)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 270.0f + 0.000001f;
							CreateMeshComponent(2, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 4: // | 90 
						{		//pDC->FillRect(rect, new CBrush(RGB(0, 0, 139)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 90.0f + 0.000001f;
							CreateMeshComponent(0, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 5: // | 90
						{
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 90.0f + 0.000001f;
							CreateMeshComponent(0, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 6: // Г
						{
							//pDC->FillRect(rect, new CBrush(RGB(184, 134, 11)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							CreateMeshComponent(2, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 7: // T -90
						{
							//pDC->FillRect(rect, new CBrush(RGB(169, 169, 169)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = -90.0f + 0.000001f;
							CreateMeshComponent(1, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 8: // |
						{
							//pDC->FillRect(rect, new CBrush(RGB(0, 100, 0)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							CreateMeshComponent(0, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 9: // Г 180
						{
							//pDC->FillRect(rect, new CBrush(RGB(189, 183, 107)));
							SpawnLocation.X = 1.0f * room.getCenterX(); //((UClass*)StaticMesh)
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 180.0f + 0.000001f;
							CreateMeshComponent(2, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 10: // |
						{
							//pDC->FillRect(rect, new CBrush(RGB(139, 0, 139)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							CreateMeshComponent(0, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 11: // T 180
						{
							//pDC->FillRect(rect, new CBrush(RGB(85, 107, 47)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 180.0f + 0.000001f;
							CreateMeshComponent(1, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 12: // Г 90 top
						{
							//pDC->FillRect(rect, new CBrush(RGB(255, 140, 0)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 90.0f + 0.000001f;
							CreateMeshComponent(2, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 13: //T 90
						{
							//pDC->FillRect(rect, new CBrush(RGB(153, 50, 204)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							SpawnRotation.Yaw = 90.0f + 0.000001f;
							CreateMeshComponent(1, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 14: //T 0
						{
							//pDC->FillRect(rect, new CBrush(RGB(139, 0, 0)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();
							CreateMeshComponent(1, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						case 15: //+
						{
							//pDC->FillRect(rect, new CBrush(RGB(233, 150, 122)));
							SpawnLocation.X = 1.0f * room.getCenterX();
							SpawnLocation.Y = 1.0f *  room.getCenterY();							
							CreateMeshComponent(3, SpawnLocation, SpawnRotation, ConvertedFString);
						}
						break;
						default: break;
					}
				


				}
				room.shift(maze->_sizeRoomXY, 0);
			}
			room.shift(-maze->_sizeRoomXY * maze->_sizeMazeY, maze->_sizeRoomXY);
		} 

}


bool AMazeGenerationLogic::SuperGenMaze()
{
	

		RegisterMazeComponent();

		
	



	return false;
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

