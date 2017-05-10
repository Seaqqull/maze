// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class PointF
{
public:
	float _first, _second;
	PointF() : _first(0), _second(0) {}
	PointF(float first, float second) : _first(first), _second(second) {}
};


class MDGEN_API Edges
{

public:
	PointF _vertexA;		//вершина 1
	PointF _vertexB;		//вершина 2
	int _WeightEdge;		//вес ребра
	int _FirstRoom;			//номер 1 комнаты 
	int _SecondRoom;		//номер 2 комнаты 
	int _NumberEdge;		//номер ребра
	bool _isDraw;			//исключение ребра

	Edges();
	Edges(float FirstvertexA, float SecondvertexA, float FirstvertexB, float SecondvertexB, double NumberEdge, int WeightEdge, int FirstRoom, int SecondRoom, bool isDraw);
	Edges(PointF vertexA, PointF vertexB, double NumberEdge, int WeightEdge, int FirstRoom, int SecondRoom, bool isDraw);
	~Edges();
};

class shortEdge
{
public:
	int _vertexA, _vertexB, _WeightEdge;
	shortEdge() {}
	shortEdge(int vertexA, int vertexB, int WeightEdge) : _vertexA(vertexA), _vertexB(vertexB), _WeightEdge(WeightEdge) {}
};