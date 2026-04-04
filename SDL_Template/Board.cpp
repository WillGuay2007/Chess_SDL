#include <iostream>
#include "Board.h"
#include "Piece.h"
#include "Tile.h"

Board::Board(SDL_Renderer* renderer)
	: m_Renderer(renderer)
	, m_selectedPiece(nullptr)
{
	InitTiles();
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete m_tiles[i][j];
			m_tiles[i][j] = nullptr;
		}
	}
}

void Board::InitTiles()
{
	for (int i = 0; i < 8; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for (int j = 0; j < 8; j++)
		{
			m_tiles[i].push_back(new Tile(m_Renderer, Vector2(j * TILE_SIZE, i * TILE_SIZE)));
		}
	}
}

void Board::Draw()
{
	for (int i = 0; i < m_tiles.size(); i++)
	{
		for (int j = 0; j < m_tiles[i].size(); j++)
		{
			m_tiles[i][j]->Draw();
			
		}
	}
	for (int i = 0; i < m_tiles.size(); i++)
	{
		for (int j = 0; j < m_tiles[i].size(); j++)
		{
			Piece* p = m_tiles[i][j]->GetOccupyingPiece();
			if (p != nullptr) p->Draw();
		}
	}
}

bool FilterTile(GridPosition pos) {
	return (pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8);
}

std::vector<GridPosition> Board::FilterInvalidTiles(std::vector<GridPosition> moves) {
	std::vector<GridPosition> validTiles;
	for (GridPosition pos : moves) {
		if (FilterTile(pos)) validTiles.push_back(pos);
	}
	return validTiles;
}

void Board::MouseMotion(const int x, const int y)
{

}

void Board::ResetHighlight() {
	for (int i = 0; i < m_tiles.size(); i++)
	{
		for (int j = 0; j < m_tiles[i].size(); j++)
		{
			m_tiles[i][j]->ResetTexture();
		}
	}
}

void Board::MouseButtonDown(Vector2 mousePos)
{
	Tile* tile = GetTile(mousePos);

	if (tile->IsHighlighted()) {
		GetTile(m_selectedPiece->GetPosition())->RemoveOccupyingPiece();
		m_selectedPiece->ChangePosition(tile->GetGridPosition());
		if (tile->GetOccupyingPiece() != nullptr) {
			Piece* p = tile->GetOccupyingPiece();
			tile->RemoveOccupyingPiece();
			delete p;
			p = nullptr;
		}
		tile->AssignPiece(m_selectedPiece);
		ResetHighlight();
		m_selectedPiece = nullptr; //Mon choix de design.
	}
	else {
		Piece* piece = tile->GetOccupyingPiece();
		if (piece == nullptr) {
			ResetHighlight();
			m_selectedPiece = nullptr; //Mon choix de design.
			return;
		}
		ResetHighlight();
		m_selectedPiece = piece;
		SetLegalMovesHighlight(piece);
	}
}

void Board::AssignPiece(GridPosition pos, Piece* piece)
{
	Tile* tile = GetTile(pos);
	if (tile->GetOccupyingPiece() != nullptr) return;
	tile->AssignPiece(piece);
}

void Board::SetLegalMovesHighlight(Piece* p) {
	if (p != nullptr) {
		auto getPieceAt = [this](GridPosition pos) -> Piece* {
			if (FilterTile(pos) == false) return nullptr;
			return GetTile(pos)->GetOccupyingPiece();
		};
		std::vector<GridPosition> legalMoves = p->GetLegalMoves(getPieceAt);
		legalMoves = FilterInvalidTiles(legalMoves);
		for (GridPosition pos : legalMoves) {
			Tile* tile = GetTile(pos);
			tile->Highlight();
		}
	}
}
