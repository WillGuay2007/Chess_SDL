#include "PieceFactory.h"
#include "Pawn.h"
#include "TransformStructs.h"

PieceFactory::PieceFactory(SDL_Renderer* renderer)
	: m_renderer(renderer)
{
}

Piece* PieceFactory::CreatePawn(GridPosition pos, PieceColor color)
{
	return new Pawn(m_renderer, pos, color);
}
