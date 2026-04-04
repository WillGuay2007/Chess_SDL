#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color);
	~Pawn() = default;
	std::vector<GridPosition> GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt) override;
};

