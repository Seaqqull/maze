// Fill out your copyright notice in the Description page of Project Settings.

#include "MDGen.h"
#include "MazeGen.h"

#include <algorithm>  
#include "MazeGenerationLogic.h"


MazeGen::MazeGen() :
	_sizeMazeX(0),
	_sizeMazeY(0),
	_sizeRoomXY(0),
	number_vertices(0)
{

}

MazeGen::MazeGen(int sizeMazeX, int sizeMazeY, int sizeRoomXY) : number_vertices(0)
	{
		_sizeMazeX = (sizeMazeX <= 2) ? 3 : sizeMazeX;
		_sizeMazeY = (sizeMazeY <= 2) ? 3 : sizeMazeY;
		_sizeRoomXY = (sizeRoomXY <= 0) ? 100 : sizeRoomXY;
	}


void MazeGen::FormLieder()
{
	for (int i = 0; i < number_vertices; i++)
		mEdge.push_back(i);
}

int MazeGen::Check(int v)
{
	if (mEdge[v] == v)
		return v;
	return mEdge[v] = Check(mEdge[v]);
}

void MazeGen::Swap(int* x, int* y)
{
	if (rand() & 1)
	{
		int* z;
		z = x;
		x = y;
		y = z;
	}
}

bool MazeGen::Union(int x, int y)
{
	x = this->Check(x);
	y = this->Check(y);
	if (x == y)
		return false;
	this->Swap(&x, &y);

	mEdge[x] = y;

	return true;
}

void MazeGen::GenerationRoom()
{
	int i, j, entrance, exit;

	Labirint.push_back(0xF);

	entrance = int(_sizeMazeX / 2);
	exit = 1 + rand() % (_sizeMazeX - 2);

	for (i = 0; i < _sizeMazeX; i++)
	{
		for (j = 0; j < _sizeMazeY; j++)
		{
			if ((i == 0) & (j > 0)) Labirint.push_back(0xE);

			if ((i == entrance) & (j == 0))
			{
				Labirint.push_back(0x6); 
				_entrance = number_vertices;
			}
			else if ((j == 0) & (i > 0)) Labirint.push_back(0x7);

			if ((i == exit) & (j == (_sizeMazeY - 1)))
			{
				Labirint.push_back(0x2); 
				_exit = number_vertices;  
			}
			else if ((j > 0) & (i > 0)) Labirint.push_back(0x6);

			number_vertices++;
			if (j != _sizeMazeY - 1)
				_MazeGen.push_back(new Wall(number_vertices, number_vertices + 1, rand() % 101, true));  //horizontal
			if (i != _sizeMazeX - 1)
				_MazeGen.push_back(new Wall(number_vertices, number_vertices + _sizeMazeY, rand() % 101, false));  //vertical	
		}
	}

}

void MazeGen::GenerationMST()
{
	sort(_MazeGen.begin(), _MazeGen.end(), SortWall<Wall>());
	FormLieder();

	int size, i, x, y;
	size = _MazeGen.size();

	for (i = 0; i < size; i++)
	{
		x = _MazeGen[i]->_vertexA;
		y = _MazeGen[i]->_vertexB;
		if (Union(x - 1, y - 1))
		{
			if (_MazeGen[i]->_orientation) // h
				Labirint[x - 1] &= 0xB;
				//Labirint[y - 1] &= 0xE;
			else // v
				Labirint[x - 1] &= 0xD;
				//Labirint[y - 1] &= 0x7;
		}

	}
}

//template<typename T>
//void MazeGen::ClearVector(std::vector<T*> &vec)
//{
//	int size = vec.size();
//	if (size == 0) return;
//	for (int i = 0; i < size; i++)
//		delete[] vec[i];
//	vec.clear();
//	vec.shrink_to_fit();
//}




