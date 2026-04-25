#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize);
	~Queen() = default;
	std::vector<GridPosition> GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt) override;
};

