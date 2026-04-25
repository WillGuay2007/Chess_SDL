#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize);
	~Pawn() = default;
	std::vector<GridPosition> GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked = nullptr) override;
	std::vector<GridPosition> GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt) override;
};

