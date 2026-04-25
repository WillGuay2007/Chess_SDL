#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize);
	~Bishop() = default;
	std::vector<GridPosition> GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt) override;
};

