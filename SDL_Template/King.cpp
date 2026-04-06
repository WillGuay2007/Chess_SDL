#include "King.h"

King::King(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
	: Piece(renderer, piecePosition, color, tileSize)
{
	LoadTexture("assets/king.png");
	if (color == Black) SetTint(50, 50, 50);
}

std::vector<GridPosition> King::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked)
{
	std::vector<GridPosition> legalMoves;
	for (GridPosition pos : GetAttackedSquares(getPieceAt)) {
		Piece* p = getPieceAt(pos);
		if (p != nullptr) {
			if (p->GetPieceColor() == color) continue;
		}
		if (isTileAttacked != nullptr && isTileAttacked(pos, GetPieceColor())) continue;
		legalMoves.push_back(pos);
	}
	return legalMoves;
}

std::vector<GridPosition> King::GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt)
{
	GridPosition kingPosition = (GridPosition)GetPosition();
	return
	{
		{
			kingPosition + GridPosition(0,1),
			kingPosition + GridPosition(-1,0),
			kingPosition + GridPosition(0,-1),
			kingPosition + GridPosition(1,0),
			kingPosition + GridPosition(1,1),
			kingPosition + GridPosition(-1,1),
			kingPosition + GridPosition(-1,-1),
			kingPosition + GridPosition(1,-1),
		}
	};
}


