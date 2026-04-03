#include "Piece.h"

Piece::Piece(SDL_Renderer* renderer, GridPosition piecePosition) : Sprite(renderer, piecePosition, TILE_SIZE) {}

Piece::~Piece()
{
}
