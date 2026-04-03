#include "Game.h"
#include <iostream>
#include "Board.h"
#include "Tile.h"

Game::Game(SDL_Renderer* renderer)
	: m_Renderer(renderer)
	, m_board(new Board(renderer))
{
}

Game::~Game()
{
	delete m_board;
}


void Game::Update()
{

}

void Game::Draw()
{
	m_board->Draw();
}

void Game::MouseMotion(const int& x, const int& y)
{
	m_board->MouseMotion(x, y);

}

void Game::MouseButtonDown(const int& x, const int& y)
{
	m_board->MouseButtonDown(x, y);

}