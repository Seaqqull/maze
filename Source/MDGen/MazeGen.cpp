// Fill out your copyright notice in the Description page of Project Settings.

#include "MDGen.h"
#include "MazeGen.h"

#include <algorithm> 


MazeGen::~MazeGen()
{
}


MazeGen::MazeGen()
{
	_sizeMazeX = _sizeMazeX = _sizeRoomXY /*= _sizeRoomY*/ = 5;
	number_vertices = 1;
}

MazeGen::MazeGen(int sizeMazeX, int sizeMazeY, int sizeRoomXY/*, int sizeRoomY*/)
{
	Dimensioning(sizeMazeX, sizeMazeY, sizeRoomXY/*, sizeRoomY*/);
}

void MazeGen::Dimensioning(int& sizeMazeX, int& sizeMazeY, int& sizeRoomXY/*, int sizeRoomY*/)
{
	//srand(unsigned(time(NULL)));
	_sizeMazeX = (sizeMazeX % 2 == 0) ? ++sizeMazeX : sizeMazeX;
	_sizeMazeY = (sizeMazeY % 2 == 0) ? ++sizeMazeY : sizeMazeY;
	_sizeRoomXY = (sizeRoomXY == 0) ? 26 : sizeRoomXY;
	_sizeRoomXY *= 100; //100 - 1 метр в ue4
	/*_sizeRoomY = sizeRoomY;*/
	number_vertices = 1;
}

void MazeGen::FormLieder(int kol_vertices)
{
	for (int i = 0; i < kol_vertices; i++)
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

void MazeGen::ClearingMemory()
{
	for (int count = 0; count < _sizeMazeX; count++)
		delete[]	Labirint[count];
}

void MazeGen::GenerationRoom()
{
	int i, j;

	Labirint = new int*[_sizeMazeX];
	for (i = 0; i < _sizeMazeX; i++)
		Labirint[i] = new int[_sizeMazeY];

	//формируем ребра графа
	for (i = 1; i < _sizeMazeX - 1; i++)
	{
		for (j = 1; j < _sizeMazeY - 1; j++)
		{
			//дл€ нечетных
			if ((i & 1) == 1 &&
				(j & 1) == 1 &&
				i < _sizeMazeX - 1 &&
				j < _sizeMazeY - 1)
			{
				Labirint[i][j] = number_vertices++;
			}
			else
			{
				if ((i & 1) == 0 && (j & 1) == 0)
					continue;		//дл€ четных
				if ((i & 1) == 1 && (j & 1) == 0)				//дл€ нечетных и четных
					Labirint[i][j] = (int)vertical;
				else Labirint[i][j] = (int)horizontal;
				_MazeGen.push_back(new shortEdge(i, j, rand() % 101));
			}

		}
	}
}

int MazeGen::GetWall(int currentX, int currentY) {
	int wall = 0;
	if (currentX - 1 >= 0 && (Labirint[currentX - 1][currentY] <= 0 && Labirint[currentX - 1][currentY] != -1))
		wall |= WALL_TOP;
	if (currentX + 1 < _sizeMazeX && (Labirint[currentX + 1][currentY] <= 0 && Labirint[currentX + 1][currentY] != -1))
		wall |= WALL_BOTTOM;

	if (currentY - 1 >= 0 && (Labirint[currentX][currentY - 1] <= 0 && Labirint[currentX][currentY - 1] != -1))
		wall |= WALL_LEFT;
	if (currentY + 1 < _sizeMazeY && (Labirint[currentX][currentY + 1] <= 0 && Labirint[currentX][currentY + 1] != -1))
		wall |= WALL_RIGHT;
	return wall;
}

void MazeGen::GenerationMST(int kol_vertices, list<Edges*> *listEdges)
{
	int x, y;

	if (listEdges != NULL) listEdges->sort(SortEdge<Edges>());
	sort(_MazeGen.begin(), _MazeGen.end(), SortEdge<shortEdge>());

	FormLieder(kol_vertices);

	if (listEdges != NULL)
	{
		int  prozent;
		prozent = ceil(listEdges->size() * 0.18f); //возвращаем % 
		for (auto pObj = listEdges->begin(); pObj != listEdges->end(); ++pObj)
		{

			x = (*pObj)->_FirstRoom;
			y = (*pObj)->_SecondRoom;

			if (!Union(x - 1, y - 1))
			{
				if ((rand() & 1) | (prozent == 0))
					(*pObj)->_isDraw = false;
				else
					prozent--;
			}
		}
		return;
	}

	int size, i;
	size = _MazeGen.size();
	for (i = 0; i < size; i++)
	{
		if (Labirint[_MazeGen[i]->_vertexA][_MazeGen[i]->_vertexB] == (int)vertical)
		{
			x = Labirint[_MazeGen[i]->_vertexA][_MazeGen[i]->_vertexB - 1];
			y = Labirint[_MazeGen[i]->_vertexA][_MazeGen[i]->_vertexB + 1];
		}
		else
		{
			x = Labirint[_MazeGen[i]->_vertexA - 1][_MazeGen[i]->_vertexB];
			y = Labirint[_MazeGen[i]->_vertexA + 1][_MazeGen[i]->_vertexB];
		}

		if (Union(x - 1, y - 1))
		{
			Labirint[_MazeGen[i]->_vertexA][_MazeGen[i]->_vertexB] = -1;
		}
	}

	//¬ход
	size = floor((_sizeMazeX - 1) * 0.5);
	if ((size & 1) == 0) size++;			//по середине
	Labirint[size][0] = -1;
	//¬ыход 
	if (rand() & 1) Labirint[_sizeMazeX - 1][_sizeMazeY - 2] = -1; // одна сторона
	else Labirint[1][_sizeMazeY - 1] = -1;				// противоположна€

	ClearVector(_MazeGen);
	mEdge.clear();

}

template<typename T>
void MazeGen::ClearVector(std::vector<T*> &vec)
{
	int size = vec.size();
	if (size == 0) return;
	for (int i = 0; i < size; i++)
		delete[] vec[i];
	vec.clear();
	vec.shrink_to_fit();
}



