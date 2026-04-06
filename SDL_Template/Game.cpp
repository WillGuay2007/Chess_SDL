#include "Game.h"
#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "King.h"

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
		if (m_whiteToPlay && KingIsInCheck(m_whiteKing) || !m_whiteToPlay && KingIsInCheck(m_blackKing)) {
			if (dynamic_cast<King*>(p) == nullptr) {
				std::cout << (m_whiteToPlay ? "White's " : "Black's ") << "king is in check. Please step away from the check.\n";
				return;
			};
		}
	}

	if (m_board->MouseButtonDown(mousePos)) m_whiteToPlay = !m_whiteToPlay;

}

bool Game::IsCorrectTurn(Piece* p) {
	return ((p->GetPieceColor() == White && m_whiteToPlay) || (p->GetPieceColor() == Black && !m_whiteToPlay));
}

bool Game::KingIsInCheck(Piece* king) {
	return m_board->IsSquareAttacked(king->GetPosition(), king->GetPieceColor());
}

void Game::InitPieces()
{
	//Pawns
	for (int i = 1; i <= 6; i = i + 5) {
		for (int j = 0; j < 8; j++) {
			Piece* pawn = m_pieceFactory->CreatePawn({ j, i }, i == 1 ? Black : White, TILE_SIZE);
			m_board->AssignPiece(pawn->GetPosition(), pawn);
		}
	}
	//Kings
	m_blackKing = m_pieceFactory->CreateKing({ 4, 0 }, Black, TILE_SIZE);
	m_board->AssignPiece(m_blackKing->GetPosition(), m_blackKing);

	m_whiteKing = m_pieceFactory->CreateKing({ 4, 7 }, White, TILE_SIZE);
	m_board->AssignPiece(m_whiteKing->GetPosition(), m_whiteKing);

}