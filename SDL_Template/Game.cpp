#include "Game.h"
#include <iostream>
#include "Board.h"
#include "Tile.h"

Game::Game(SDL_Renderer* renderer)
	: m_Renderer(renderer)
	, m_board(new Board(renderer))
	, m_pieceFactory(new PieceFactory(renderer))
{
	InitPieces();
}

Game::~Game()
{
	delete m_board;
	m_board = nullptr;
	delete m_pieceFactory;
	m_pieceFactory = nullptr;
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

void Game::MouseButtonDown(Vector2 mousePos)
{
	Tile* tile = m_board->GetTile(mousePos);
	Piece* p = tile->GetOccupyingPiece();

	if (!tile->IsHighlighted()) {
		if (p != nullptr && !IsCorrectTurn(p)) return;
	}

	if (m_board->MouseButtonDown(mousePos)) m_whiteToPlay = !m_whiteToPlay;

}

bool Game::IsCorrectTurn(Piece* p) {
	return ((p->GetPieceColor() == White && m_whiteToPlay) || (p->GetPieceColor() == Black && !m_whiteToPlay));
}

void Game::InitPieces()
{
	//Pawns
	for (int i = 1; i <= 6; i = i + 5) {
		for (int j = 0; j < 8; j++) {
			Piece* pawn = m_pieceFactory->CreatePawn({ j, i }, i == 1 ? Black : White);
			m_board->AssignPiece(pawn->GetGridPosition(), pawn);
		}
	}


}