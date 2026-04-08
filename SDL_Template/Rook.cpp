#include "Rook.h"

Rook::Rook(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
    : Piece(renderer, piecePosition, color, tileSize)
{
    LoadTexture("assets/rook.png");
    if (color == Black) SetTint(50, 50, 50);
}

std::vector<GridPosition> Rook::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked)
{
    std::vector<GridPosition> possibleMoves = GetAttackedSquares(getPieceAt);
    std::vector<GridPosition> legalMoves;
    for (GridPosition pos : possibleMoves) {
        Piece* p = getPieceAt(pos);
        if (p != nullptr && p->GetPieceColor() == color) continue;
        legalMoves.push_back(pos);
    }
    return legalMoves;
}

std::vector<GridPosition> Rook::GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt)
{
    GridPosition rookPosition = GetPosition();
    std::vector<GridPosition> moves;
    for (int i = -1; i <= 1; i = i + 2) {
        for (int j = 1; j < 8; j++) {
            GridPosition pos = rookPosition + GridPosition(0, j * i);
            if (getPieceAt(pos) != nullptr) { moves.push_back(pos); break; }
            moves.push_back(pos);
        }
    }
    for (int i = -1; i <= 1; i = i + 2) {
        for (int j = 1; j < 8; j++) {
            GridPosition pos = rookPosition + GridPosition(j * i, 0);
            if (getPieceAt(pos) != nullptr) { moves.push_back(pos); break; }
            moves.push_back(pos);
        }
    }
    return moves;
}
