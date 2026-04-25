#pragma once
#include "SDL.h"
#include "Sprite.h"
#include "Board.h"
#include "PieceFactory.h"

class King;

class Game
{

public:
	Game(SDL_Renderer* renderer);
	~Game();


	void Draw();
	void MouseMotion(Vector2 mousePos);
	void MouseButtonDown(Vector2 mousePos);
	void MouseButtonUp(Vector2 mousePos);
	bool IsCorrectTurn(Piece* p);
	void InitPieces();

private:
	bool m_whiteToPlay = true;
	SDL_Renderer* m_Renderer;
	Board* m_board;
	PieceFactory* m_pieceFactory;
	King* m_whiteKing;
	King* m_blackKing;
	bool m_gameOver = false;
};

