#include "Tile.h"
#include "Sprite.h"
#include <iostream>

//C'est le constructeur! Reset texture c'est pour son teint ca la reset pas litteralement.
Tile::Tile(SDL_Renderer* renderer, Vector2 pos)
	: Sprite(renderer, pos, TILE_SIZE)
	, m_occupyingPiece(nullptr)
{
	LoadTexture(("assets/tile.png"));
	ResetTexture();
}

//c'est le destructeur!!
Tile::~Tile()
{
	if (m_occupyingPiece == nullptr) return;
	delete m_occupyingPiece;
	m_occupyingPiece = nullptr;
}

//Ca verifie si la tuile est noire
bool Tile::IsBlack() {
	GridPosition pos = (GridPosition)GetPosition();
	return (pos.column + pos.row) % 2 == 0;
}

//Ca verifie si la tuile est highlighted
bool Tile::IsHighlighted()
{
	return m_isHighlighted;
}

//Ca set le occupying piece de la tuile.
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
	//Les tuiles "noires" vont avoir un teint plus foncé.
	if (IsBlack()) { SetTint(200, 100, 100); } else { SetTint(255, 128, 128); };
}

void Tile::SetSelectionColor()
{
	SetTint(100, 200, 200);
}

//Ca remet le teint par défaut de la tuile.
void Tile::ResetTexture()
{
	m_isHighlighted = false;
	if (IsBlack()) { SetTint(128, 128, 128); } else { SetTint(255, 255, 255); };
}

void Tile::ShowIndex()
{
	//Puisque Gridposition a un constructeur qui prend un vector2, le cast marche et ca te donne l'index de la tuile.
	//Utile pour le debug seulement
	GridPosition pos = (GridPosition)GetPosition();

	std::cout << pos.column << " - " << pos.row << std::endl;
}
