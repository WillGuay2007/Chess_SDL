#include "Pawn.h"

Pawn::Pawn(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize) 
    : Piece(renderer, piecePosition, color, tileSize)
{
    LoadTexture("assets/pawn.png");
    if (color == Black) SetTint(50, 50, 50);
}

//Je override parce que le mouvement d'un pion est plus spefifique qu'une piece reguliere. j'ai pas le move "en passant" vu que cetais pas demande
std::vector<GridPosition> Pawn::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked)
{
    GridPosition pawnPosition = (GridPosition)GetPosition();

    //Basic pawn push.
    std::vector<GridPosition> legalMoves;
    GridPosition pushForward = pawnPosition + GridPosition(0, color);
    if (getPieceAt(pushForward) == nullptr) legalMoves.push_back(pushForward);

    //Double pawn push
    if ((pawnPosition.row == 6 && color == White) || (pawnPosition.row == 1 && color == Black)) {
        GridPosition doublePush = pawnPosition + GridPosition(0, color * 2);
        if (getPieceAt(doublePush) == nullptr && getPieceAt(pushForward) == nullptr) legalMoves.push_back(doublePush);
    }

    //Capture
    GridPosition DiagonalRight = pawnPosition + GridPosition(1, color);
    GridPosition DiagonalLeft = pawnPosition + GridPosition(-1, color);

    if (getPieceAt(DiagonalRight) != nullptr && getPieceAt(DiagonalRight)->IsEnemy(color)) legalMoves.push_back(DiagonalRight);
    if (getPieceAt(DiagonalLeft) != nullptr && getPieceAt(DiagonalLeft)->IsEnemy(color)) legalMoves.push_back(DiagonalLeft);

    return legalMoves;
}

std::vector<GridPosition> Pawn::GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt)
{
    GridPosition pawnPosition = (GridPosition)GetPosition();
    return { pawnPosition + GridPosition(1,color), pawnPosition + GridPosition(-1,color) };
}
