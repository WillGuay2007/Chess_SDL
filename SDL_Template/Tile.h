#pragma once
#include <SDL.h>
#include "Sprite.h"

class Piece;

class Tile : public Sprite
{
public:
	Tile(SDL_Renderer* renderer, Vector2 pos);

	Piece* GetOccupyingPiece() { return m_occupyingPiece; }
	void RemoveOccupyingPiece() { m_occupyingPiece = nullptr; }
	void AssignPiece(Piece* piece);
	void Highlight();
	void ResetTexture();
	void ShowIndex();
	bool IsBlack();
	bool IsHighlighted();
private:
	Piece* m_occupyingPiece;
	bool m_isHighlighted;
};