#pragma once
#include <SDL.h>
#include <vector>

class Tile;

class Board
{
public:
	Board(SDL_Renderer* renderer);
	virtual ~Board();

	void Draw();

	void MouseMotion(const int x, const int y);
	void MouseButtonDown(const int& x, const int& y);

private:

	void InitTiles();

	SDL_Renderer* m_Renderer;
	std::vector<std::vector<Tile*>> m_Tiles;
};

