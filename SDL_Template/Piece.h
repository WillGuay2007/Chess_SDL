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
	Piece(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color);
	~Piece();
	virtual std::vector<GridPosition> GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt) = 0;
	void ChangePosition(GridPosition newPos);
	bool IsEnemy(PieceColor _color) { return color != _color; }
protected:
	PieceColor color;
};

