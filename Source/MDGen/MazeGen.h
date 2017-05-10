// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <list>
#include <vector>
#include <time.h>
#include "Edges.h"
#include "Room.h"

using namespace std;

template <class R>
class SortEdge
{
public:
	bool operator() (const R *first, const R *second)
	{
		return  (first->_WeightEdge == second->_WeightEdge) ? 0 : ((first->_WeightEdge < second->_WeightEdge) ? 1 : 0);
	}
};


class MDGEN_API MazeGen
{
private:
	enum Direction { vertical = -3, horizontal };	//для генерации сетки
													//int RoomStateIsFree;						// if > 1 then create enum. комната является проходом
	int  number_vertices;						//количество вершин
	vector<shortEdge*> _MazeGen;					//ребра
	vector<int> mEdge;							//хранит номера вершин

private:
	void FormLieder(int number_vertices);
	int Check(int v);
	void Swap(int* x, int* y);
	bool Union(int x, int y);

	template<typename T>
	void ClearVector(std::vector<T*> &vec);
	void GenerationRoom();

	const int WALL_TOP = 1
		, WALL_RIGHT = 2
		, WALL_BOTTOM = 4
		, WALL_LEFT = 8;

public:
	int** Labirint;								//сетка хранящая комнаты и стены
	int _sizeMazeX, _sizeMazeY, _sizeRoomXY/*, _sizeRoomY*/;
	bool isGenerationMaze = false;
	void Dimensioning(int sizeX, int sizeY, int sizeRoomXY/*, int sizeRoomY*/);

	MazeGen();
	~MazeGen();
	MazeGen(int sizeMazeX, int sizeMazeY, int sizeRoomXY/*, int sizeRoomY*/);

	void GenerationMST(int number_vertices, list<Edges*> *listEdges = NULL);
	int GetWall(int currentX, int currentY);

	void GenerationMaze()
	{
		GenerationRoom();
		GenerationMST(number_vertices);
	}

};
