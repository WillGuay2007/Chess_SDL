#pragma once

#include "SDL_image.h"
#include "Piece.h"

class PieceFactory
{
public:
	PieceFactory(SDL_Renderer* renderer);
	~PieceFactory() = default;
	Piece* CreatePawn(GridPosition pos, PieceColor color, int tileSize);
	Piece* CreateKing(GridPosition pos, PieceColor color, int tileSize);
private:
	SDL_Renderer* m_renderer;
};

