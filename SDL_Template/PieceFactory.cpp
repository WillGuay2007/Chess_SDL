#include "PieceFactory.h"
#include "Pawn.h"
#include "King.h"
#include "TransformStructs.h"

PieceFactory::PieceFactory(SDL_Renderer* renderer)
	: m_renderer(renderer)
{
}

Piece* PieceFactory::CreatePawn(GridPosition pos, PieceColor color, int tileSize)
{
	return new Pawn(m_renderer, pos, color, tileSize);
}

Piece* PieceFactory::CreateKing(GridPosition pos, PieceColor color, int tileSize)
{
	return new King(m_renderer, pos, color, tileSize);
}
