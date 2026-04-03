#pragma once
#include <SDL.h>
#include "Sprite.h"

class Piece;

class Tile : public Sprite
{
public:
	Tile(SDL_Renderer* renderer, Vector2 pos);

	void ShowIndex();
private:
	Piece* m_occupyingPiece;
};