#include <iostream>
#include "Bishop.h"

Bishop::Bishop(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
    : Piece(renderer, piecePosition, color, tileSize)
{
    LoadTexture("assets/bishop.png");
    if (color == Black) SetTint(50, 50, 50);
}

std::vector<GridPosition> Bishop::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked)
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

std::vector<GridPosition> Bishop::GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt)
{
    GridPosition bishopPosition = GetPosition();
    std::vector<GridPosition> moves;
    for (int i = 0; i < 4; i++) {
        //Ca a l'air bizarre le code mais dans le fond j'ai spot le pattern des bits (0-0, 0-1, 1-0, 1-1) et j'ai vu que ca match les combinaisons du fou. (-1,-1 et -1,1 et 1,-1 et 1,1) donc en vrai ca fait du sens
        //Il avait surement une facon plus facile mais pas grave je l'ai pas trouvé, ca me tentais pas de faire quatre for loops.
        int firstBit = i % 2;
        int secondBit = i / 2;
        //Ici je fais 8 (je sais que ca peut sortir des bounds mais le board qui le recoit va filtrer ces squares)
        for (int j = 1; j < 8; j++) {
            GridPosition pos = bishopPosition + GridPosition(firstBit == 0 ? j : -j, secondBit == 0 ? j : -j);
            if (getPieceAt(pos)) { moves.push_back(pos); break; }
            moves.push_back(pos);
        }
    }
    
    
    return moves;
}
