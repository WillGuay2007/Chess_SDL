#include "Piece.h"

Piece::Piece(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color)
	: Sprite(renderer, piecePosition, TILE_SIZE)
	, color(color) 
{}

Piece::~Piece()
{
}

void Piece::ChangePosition(GridPosition newPos)
{
	SetGridPosition(newPos);
}
