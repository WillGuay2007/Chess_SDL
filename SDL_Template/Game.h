#pragma once
#include "SDL.h"
#include "Sprite.h"
#include "Board.h"
#include "PieceFactory.h"

class Game
{

public:
	Game(SDL_Renderer* renderer);
	~Game();


	void Update();
	void Draw();
	void MouseMotion(const int& x, const int& y);
	void MouseButtonDown(const int& x, const int& y);
	void InitPieces();

private:

	SDL_Renderer* m_Renderer;
	Board* m_board;
	PieceFactory* m_pieceFactory;
};

