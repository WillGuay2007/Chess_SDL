#include "Board.h"
#include "Tile.h"
#include <iostream>

Board::Board(SDL_Renderer* renderer)
	: m_Renderer(renderer)
{
	InitTiles();
}

Board::~Board()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			delete m_Tiles[i][j];
			m_Tiles[i][j] = nullptr;
		}
	}
}

void Board::InitTiles()
{
	for (int i = 0; i < 9; i++)
	{
		m_Tiles.push_back(std::vector<Tile*>());
		for (int j = 0; j < 9; j++)
		{
			m_Tiles[i].push_back(new Tile(m_Renderer, Vector2(j * TILE_SIZE, i * TILE_SIZE)));
		}
	}
}

void Board::Draw()
{
	for (int i = 0; i < m_Tiles.size(); i++)
	{
		for (int j = 0; j < m_Tiles[i].size(); j++)
		{
			m_Tiles[i][j]->Draw();
		}
	}
}

void Board::MouseMotion(const int x, const int y)
{

}

void Board::MouseButtonDown(const int& x, const int& y)
{
	int i = y / 100;
	int j = x / 100;

	m_Tiles[i][j]->ShowIndex();
}
