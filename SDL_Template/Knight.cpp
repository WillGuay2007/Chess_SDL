#include "Knight.h"

Knight::Knight(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
    : Piece(renderer, piecePosition, color, tileSize)
{
    LoadTexture("assets/knight.png");
    if (color == Black) SetTint(50, 50, 50);
}

std::vector<GridPosition> Knight::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked)
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

std::vector<GridPosition> Knight::GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt)
{
    GridPosition knightPosition = GetPosition();
    return {
        {knightPosition + GridPosition(1,2)},
        {knightPosition + GridPosition(2,1)},
        {knightPosition + GridPosition(2,-1)},
        {knightPosition + GridPosition(1,-2)},
        {knightPosition + GridPosition(-1,-2)},
        {knightPosition + GridPosition(-2,-1)},
        {knightPosition + GridPosition(-2,1)},
        {knightPosition + GridPosition(-1,2)},
    };
}
