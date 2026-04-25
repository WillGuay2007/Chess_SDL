#include "PieceFactory.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "TransformStructs.h"

//Ca me tentais de creer une factorie je sais pas pourquoi mais c'est plus clean et plus d'abstraction!

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

Piece* PieceFactory::CreateKnight(GridPosition pos, PieceColor color, int tileSize)
{
	return new Knight(m_renderer, pos, color, tileSize);
}

Piece* PieceFactory::CreateBishop(GridPosition pos, PieceColor color, int tileSize)
{
	return new Bishop(m_renderer, pos, color, tileSize);
}

Piece* PieceFactory::CreateRook(GridPosition pos, PieceColor color, int tileSize)
{
	return new Rook(m_renderer, pos, color, tileSize);
}

Piece* PieceFactory::CreateQueen(GridPosition pos, PieceColor color, int tileSize)
{
	return new Queen(m_renderer, pos, color, tileSize);
}
