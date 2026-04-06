#include "Piece.h"

Piece::Piece(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
	: Sprite(renderer, piecePosition, tileSize, tileSize)
	, color(color) 
{}

Piece::~Piece()
{
}