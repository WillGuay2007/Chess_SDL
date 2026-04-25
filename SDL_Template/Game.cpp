#include "Game.h"
#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "King.h"

//c'est le constructeur! il initalise automatiquement les pieces a la construction
Game::Game(SDL_Renderer* renderer)
	: m_Renderer(renderer)
	, m_board(new Board(renderer))
	, m_pieceFactory(new PieceFactory(renderer))
{
	InitPieces();
}

//C'est le destructeur!
Game::~Game()
{
	delete m_board;
	m_board = nullptr;
	delete m_pieceFactory;
	m_pieceFactory = nullptr;
}

//Ca dessine le board
void Game::Draw()
{
	m_board->Draw();
}

//Ca gere le input vers le board
void Game::MouseMotion(Vector2 mousePos)
{
	m_board->MouseMotion(mousePos);
}

void Game::MouseButtonUp(Vector2 mousePos) {
	//rien faire si la partie est fini
	if (m_gameOver) return;

	Tile* releaseTile = m_board->GetTile(mousePos);
	if (!releaseTile->IsHighlighted()) m_board->ResetHighlights();

	//OnMouseClick return true si un coup a été joué.
	if (m_board->DropPiece(mousePos)) {
		m_whiteToPlay = !m_whiteToPlay;
		PieceColor turnColor = m_whiteToPlay ? PieceColor::White : PieceColor::Black;
		if (!m_board->HasAnyLegalMove(turnColor)) {
			m_gameOver = true;
			GridPosition kingPos = m_board->FindKingPosition(turnColor);
			if (m_board->IsSquareAttacked(kingPos, turnColor)) {
				std::cout << "Checkmate!\n";
			}
			else {
				std::cout << "Stalemate!\n";
			}
		}
	} 
}

//Ca te laisse seulement cliquer sur les tuiles qui sont pas deja highlight. c'est principalement pour la selection de piece qui est gere dans le board
void Game::MouseButtonDown(Vector2 mousePos)
{
	if (m_gameOver) {
		std::cout << "Game has ended. please exit the program.\n";
		return;
	}
	Tile* clickedTile = m_board->GetTile(mousePos);
	Piece* clickedPiece = clickedTile->GetOccupyingPiece();
	if (!clickedTile->IsHighlighted()) {
		if (clickedPiece != nullptr && !IsCorrectTurn(clickedPiece)) return;
	}
	else return;
	m_board->SelectPiece(mousePos);
}

//C'est pour rendre le code plus lisible. Le nom est self explanatory.
bool Game::IsCorrectTurn(Piece* p) {
	return ((p->GetPieceColor() == White && m_whiteToPlay) || (p->GetPieceColor() == Black && !m_whiteToPlay));
}

//Ca place toutes les pieces de chaque couleurs.
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
	m_blackKing = dynamic_cast<King*>(m_pieceFactory->CreateKing({ 4, 0 }, Black, TILE_SIZE));
	m_board->AssignPiece(m_blackKing->GetPosition(), m_blackKing);

	m_whiteKing = dynamic_cast<King*>(m_pieceFactory->CreateKing({ 4, 7 }, White, TILE_SIZE));
	m_board->AssignPiece(m_whiteKing->GetPosition(), m_whiteKing);

	//Knights
	for (int i = 1; i <= 6; i = i + 5) {
		for (int j = 0; j <= 1; j++) {
			Piece* knight = m_pieceFactory->CreateKnight({ i, j * 7 }, j == 0 ? Black : White, TILE_SIZE);
			m_board->AssignPiece(knight->GetPosition(), knight);
		}
	}

	//Bishops
	for (int i = 2; i <= 5; i = i + 3) {
		for (int j = 0; j <= 1; j++) {
			Piece* bishop = m_pieceFactory->CreateBishop({ i, j * 7 }, j == 0 ? Black : White, TILE_SIZE);
			m_board->AssignPiece(bishop->GetPosition(), bishop);
		}
	}

	//Rooks
	for (int i = 0; i <= 7; i = i + 7) {
		for (int j = 0; j <= 1; j++) {
			Piece* rook = m_pieceFactory->CreateRook({ i, j * 7 }, j == 0 ? Black : White, TILE_SIZE);
			m_board->AssignPiece(rook->GetPosition(), rook);
		}
	}

	//Queens
	for (int i = 0; i <= 1; i++) {
		Piece* queen = m_pieceFactory->CreateQueen({ 3, i * 7 }, i == 0 ? Black : White, TILE_SIZE);
		m_board->AssignPiece(queen->GetPosition(), queen);
	}

}