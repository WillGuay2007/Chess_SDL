#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize);
	~Knight() = default;
	std::vector<GridPosition> GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt) override;
};

