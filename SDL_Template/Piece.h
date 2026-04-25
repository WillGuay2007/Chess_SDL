#pragma once

#include "Sprite.h"
#include <vector>
#include "functional"

enum PieceColor {
	White = -1,
	Black = 1
};

class Piece : public Sprite
{
public:
	Piece(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize);
	~Piece();
	virtual std::vector<GridPosition> GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool (GridPosition, PieceColor)> isTileAttacked = nullptr);
	virtual std::vector<GridPosition> GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt) = 0;
	bool IsEnemy(PieceColor _color) { return color != _color; }
	PieceColor GetPieceColor() { return color; }
protected:
	PieceColor color;
};

