#pragma once
#include <SDL.h>
#include <vector>
#include "TransformStructs.h"
#include "Piece.h"

class Tile;

class Board
{
public:
	Board(SDL_Renderer* renderer);
	virtual ~Board();

	void Draw();

	bool IsPositionInBounds(GridPosition pos);
	void MouseMotion(Vector2 mousePos);
	void ResetHighlights();
	void SelectPiece(Vector2 mousePos);
	void MovePieceAndCapture(Piece* pieceToMove, GridPosition destination);
	void AssignPiece(GridPosition pos, Piece* piece);
	void SetLegalMovesHighlight(Piece* p);
	bool IsKingInCheckAfterMove(Piece* pieceToMove, GridPosition move);
	bool HasAnyLegalMove(PieceColor colorToCheck);
	Tile* GetTile(GridPosition pos) { return m_tiles[pos.row][pos.column]; }
	Tile* GetTile(Vector2 pos) { return GetTile((GridPosition)pos); }
	Piece* SimulateMove(Piece* pieceToMove, GridPosition destination);
	GridPosition FindKingPosition(PieceColor requiredColor);
	bool DropPiece(Vector2 mousePos);
	void UndoMove(Piece* movedPiece, GridPosition originalPos, Piece* capturedPiece, GridPosition destination);
	std::vector<GridPosition> FilterOutOfBoundsTiles(std::vector<GridPosition> moves);
	bool IsSquareAttacked(GridPosition pos, PieceColor pieceColor);

private:

	void InitTiles();
	Vector2 m_dragOrigin { 0, 0 };
	Piece* GetPieceAt(GridPosition pos);

	Piece* m_selectedPiece;
	SDL_Renderer* m_Renderer;
	std::vector<std::vector<Tile*>> m_tiles;
};

