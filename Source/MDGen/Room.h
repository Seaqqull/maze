// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <iostream> 

#define min(a,b) (((a) < (b)) ? (a) : (b))

class MDGEN_API Room
{
private:
	int _left, _right, _top, _bottom;

	void NormalizeRect(Room& r)
	{
		if (_left > _right) std::swap(_left, _right);
		if (_top > _bottom) std::swap(_top, _bottom);
		if (r._left > r._right) std::swap(r._left, r._right);
		if (r._top > r._bottom) std::swap(r._top, r._bottom);
	}
public:
	Room() : _left(0), _right(0), _top(0), _bottom(0) {	/*...*/ }
	Room(int x, int y, int width, int height) {
		_left = x;
		_right = x;
		if (width < 0)
			_left += width;
		else
			_right += width;

		_bottom = y;
		_top = y;
		if (height < 0)
			_bottom += height;
		else
			_top += height;
	}
	~Room();
	bool isIntersect(Room& r)
	{

		return!(r.getLeft() >= getRight() ||
			r.getRight() <= getLeft() ||
			r.getTop() <= getBottom() ||
			r.getBottom() >= getTop());

		/*NormalizeRect(r);

		int cx1, cy1, cx2, cy2, square;

		// Вычисляем прямоугольник С - пересечение
		cx1 = max(_left, r._left);
		cy1 = max(_top, r._top);
		cx2 = min(_right, r._right);
		cy2 = min(_bottom, r._bottom);

		// Если пересечения не существует или оно вырождено,
		// то прямоугольник C будет ненормализован или вырожден

		// Площадь, если невырожденное пересечение существует
		square = cx2 > cx1 && cy2 > cy1 ? (cx2 - cx1) * (cy2 - cy1) : 0;

		return (square > 0);*/

	}

	void SetRoom(int x, int y, int width, int height)
	{
		_left = x;
		_right = x;
		if (width < 0)
			_left += width;
		else
			_right += width;

		_bottom = y;
		_top = y;
		if (height < 0)
			_bottom += height;
		else
			_top += height;
	}

	bool touches(Room& b, int padding) {
		return !(b.getLeft() - padding >= getRight() ||
			b.getRight() <= getLeft() - padding ||
			b.getTop() <= getBottom() - padding ||
			b.getBottom() - padding >= getTop());
	}

	void expand(int by) {
		_left -= by;
		_right += by;
		_top += by;
		_bottom -= by;
	}

	int getArea() {
		return getWidth()*getHeight();
	}

	int getWidth() {
		return _right - _left;
	}

	int getHeight() {
		return _top - _bottom;
	}

	int getLeft() {
		return _left;
	}

	int getRight() {
		return _right;
	}

	int getTop() {
		return _top;
	}

	int getBottom() {
		return _bottom;
	}

	double getCenterX() {
		return (_left + _right) / 2.0;
	}

	double getCenterY() {
		return (_top + _bottom) / 2.0;
	}

	double getRatio() {
		return getRatio(getWidth(), getHeight());
	}

	double getRatio(int width, int height) {
		if (width > height)
			return width / ((double)height);
		else
			return height / ((double)width);
	}

	static void expandAll(std::vector<Room*> rooms, int by) 
	{
		for (Room* room : rooms)
			room->expand(by);
	}

	void shift(const int& x, const int& y) {
		_left += x;
		_right += x;
		_top += y;
		_bottom += y;
	}


};
