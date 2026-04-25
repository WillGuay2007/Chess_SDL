#include "Knight.h"

//C'est le constructeur!
Knight::Knight(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
    : Piece(renderer, piecePosition, color, tileSize)
{
    LoadTexture("assets/knight.png");
    if (color == Black) SetTint(50, 50, 50);
}

//Ca retourne une liste des cases que la piece attaque.
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
