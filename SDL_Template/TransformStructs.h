#pragma once
#include "GameSettings.h"

struct GridPosition;

struct Vector2 {
	Vector2(int _x, int _y) : x(_x), y(_y) {}
	Vector2(GridPosition gridPos);
	Vector2() = default;
	int x;
	int y;
};

struct GridPosition {
	GridPosition(int _column, int _row) : column(_column), row(_row) {}
	GridPosition(Vector2 position) : column(position.x / TILE_SIZE), row(position.y / TILE_SIZE) {}
	GridPosition() = default;
	Vector2 operator*(const int multiplicator) const { return { column * multiplicator, row * multiplicator }; }
	GridPosition operator+ (const GridPosition pos) const { return {column + pos.column, row + pos.row}; }
	bool operator== (const GridPosition pos) const { return (pos.column == column && pos.row == row); }
	int row;
	int column;
};

struct Size {
	Size(int w, int h) : width(w), height(h) {}
	Size(int dimensions) :width(dimensions), height(dimensions) {}
	int width;
	int height;
};