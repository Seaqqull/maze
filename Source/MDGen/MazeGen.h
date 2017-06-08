// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <list>
#include <vector>
#include <time.h>
#include "Edges.h"
#include "Room.h"
#include <bitset> 

using namespace std;

template <class R>
class SortWall
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
	int  number_vertices;							//количество вершин	
	vector<Wall*> _MazeGen;							//стены 
	vector<int> mEdge;								//хранит номера вершин
private:
	void FormLieder();
	int Check(int v);
	void Swap(int* x, int* y);
	bool Union(int x, int y);

	template<typename T>
	void ClearVector(std::vector<T*> &vec);
	void GenerationRoom();

public:
	vector<bitset<4>> Labirint;								//сетка хранящая комнаты  
	int _sizeMazeX, _sizeMazeY, _sizeRoomXY, _entrance, _exit;
	bool isGenerationMaze = false;

	MazeGen();
	MazeGen(int sizeMazeX, int sizeMazeY, int sizeRoomXY);

	void GenerationMST();
	inline bool GetWallOrientation(int index_wall) { return _MazeGen[index_wall]->_orientation; }

	void ClearMemory()
	{
		ClearVector(_MazeGen);
		mEdge.clear();
		
		Labirint.clear();
		Labirint.shrink_to_fit();
		
		number_vertices = 0;
		_entrance = 0;
		_exit = 0;
	}

	void GenerationMaze()
	{
		GenerationRoom();
		GenerationMST();
	}
};
