// Fill out your copyright notice in the Description page of Project Settings.

#include "MDGen.h"
#include "Edges.h"

Edges::Edges() {	}

Edges::Edges(float FirstvertexA, float SecondvertexA, float FirstvertexB, float SecondvertexB, double NumberEdge,
	int WeightEdge, int FirstRoom, int SecondRoom, bool isDraw)
{
	_vertexA._first = FirstvertexA;
	_vertexA._second = SecondvertexA;
	_vertexB._first = FirstvertexB;
	_vertexB._second = SecondvertexB;
	_WeightEdge = WeightEdge;
	_FirstRoom = FirstRoom;
	_SecondRoom = SecondRoom;
	_NumberEdge = NumberEdge;
	_isDraw = isDraw;
}

Edges::Edges(PointF vertexA, PointF vertexB, double NumberEdge, int WeightEdge, int FirstRoom, int SecondRoom, bool isDraw)
{
	_vertexA = vertexA;
	_vertexB = vertexB;
	_WeightEdge = WeightEdge;
	_FirstRoom = FirstRoom;
	_SecondRoom = SecondRoom;
	_NumberEdge = NumberEdge;
	_isDraw = isDraw;
}

Edges::~Edges()
{
}
