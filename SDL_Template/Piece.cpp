#include "Piece.h"

Piece::Piece(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
	: Sprite(renderer, piecePosition, tileSize, tileSize)
	, color(color) 
{}

//Pas besoin de rien detruire ici le sprite il gere et oui jai mis en virtual.
Piece::~Piece()
{
}

//Vu que ca se ressemble pour beaucoup de pieces j'ai deplace la repetition ici dans la classe de base pis je l'ai garde en virtuel pour le roi et pion.
std::vector<GridPosition> Piece::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked) {
    std::vector<GridPosition> legalMoves;
    for (GridPosition pos : GetAttackedSquares(getPieceAt)) {
        Piece* p = getPieceAt(pos);
        if (p != nullptr && p->GetPieceColor() == color) continue;
        legalMoves.push_back(pos);
    }
    return legalMoves;
}