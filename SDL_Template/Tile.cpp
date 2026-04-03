#include "Tile.h"
#include "Sprite.h"
#include <iostream>

Tile::Tile(SDL_Renderer* renderer, Vector2 pos)
	: Sprite(renderer, pos, TILE_SIZE)
{
	LoadTexture(((pos.x / TILE_SIZE + pos.y / TILE_SIZE) % 2) ? "assets/blackTile.png" : "assets/whiteTile.png");
}

void Tile::ShowIndex()
{
	GridPosition pos = GetGridPosition();

	std::cout << pos.column << " - " << pos.row << std::endl;
}
