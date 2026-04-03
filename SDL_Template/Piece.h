#pragma once

#include "Sprite.h"
#include <vector>

class Piece : public Sprite
{
public:
	Piece(SDL_Renderer* renderer, GridPosition piecePosition);
	~Piece();
	virtual std::vector<GridPosition> GetLegalMoves() = 0;
private:
	GridPosition* m_position;
};

