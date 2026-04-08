#include "Queen.h"

Queen::Queen(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
    : Piece(renderer, piecePosition, color, tileSize)
{
    LoadTexture("assets/queen.png");
    if (color == Black) SetTint(50, 50, 50);
}

std::vector<GridPosition> Queen::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked)
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

std::vector<GridPosition> Queen::GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt)
{
    //J'ai juste copié le code du fou et de la tour.
    GridPosition queenPosition = GetPosition();
    std::vector<GridPosition> moves;

    for (int i = -1; i <= 1; i = i + 2) {
        for (int j = 1; j < 8; j++) {
            GridPosition pos = queenPosition + GridPosition(0, j * i);
            if (getPieceAt(pos) != nullptr) { moves.push_back(pos); break; }
            moves.push_back(pos);
        }
    }
    for (int i = -1; i <= 1; i = i + 2) {
        for (int j = 1; j < 8; j++) {
            GridPosition pos = queenPosition + GridPosition(j * i, 0);
            if (getPieceAt(pos) != nullptr) { moves.push_back(pos); break; }
            moves.push_back(pos);
        }
    }

    for (int i = 0; i < 4; i++) {
        int firstBit = i % 2;
        int secondBit = i / 2;
        for (int j = 1; j < 8; j++) {
            GridPosition pos = queenPosition + GridPosition(firstBit == 0 ? j : -j, secondBit == 0 ? j : -j);
            if (getPieceAt(pos)) { moves.push_back(pos); break; }
            moves.push_back(pos);
        }
    }
    return moves;
}
