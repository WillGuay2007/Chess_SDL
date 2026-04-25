#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize);
	~Rook() = default;
	std::vector<GridPosition> GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt) override;
};

