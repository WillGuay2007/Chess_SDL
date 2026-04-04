#include "Tile.h"
#include "Sprite.h"
#include <iostream>

Tile::Tile(SDL_Renderer* renderer, Vector2 pos)
	: Sprite(renderer, pos, TILE_SIZE)
	, m_occupyingPiece(nullptr)
{
	LoadTexture(("assets/tile.png"));
	ResetTexture();
}

bool Tile::IsBlack() {
	return (GetGridPosition().column + GetGridPosition().row) % 2 == 0;
}

bool Tile::IsHighlighted()
{
	return m_isHighlighted;
}


void Tile::AssignPiece(Piece* piece)
{
	if (piece == nullptr) {
		std::cout << "Piece provided in AssignPiece of Tile is null. Please provide an existing piece.\n";
		return;
	}
	m_occupyingPiece = piece;
}

void Tile::Highlight()
{
	m_isHighlighted = true;
	if (IsBlack()) { SetTint(200, 100, 100); } else { SetTint(255, 128, 128); };
}

void Tile::ResetTexture()
{
	m_isHighlighted = false;
	if (IsBlack()) { SetTint(128, 128, 128); } else { SetTint(255, 255, 255); };
}

void Tile::ShowIndex()
{
	GridPosition pos = GetGridPosition();

	std::cout << pos.column << " - " << pos.row << std::endl;
}
