#pragma once
#include <SDL.h>
#include <vector>
#include "TransformStructs.h"

class Piece;
class Tile;

class Board
{
public:
	Board(SDL_Renderer* renderer);
	virtual ~Board();

	void Draw();


	void MouseMotion(const int x, const int y);
	void ResetHighlight();
	bool MouseButtonDown(Vector2 mousePos);
	void AssignPiece(GridPosition pos, Piece* piece);
	void SetLegalMovesHighlight(Piece* p);
	Tile* GetTile(GridPosition pos) { return m_tiles[pos.row][pos.column]; }
	Tile* GetTile(Vector2 pos) { return GetTile((GridPosition)pos); }
	std::vector<GridPosition> FilterInvalidTiles(std::vector<GridPosition> moves);

private:

	void InitTiles();

	Piece* m_selectedPiece;
	SDL_Renderer* m_Renderer;
	std::vector<std::vector<Tile*>> m_tiles;
};

