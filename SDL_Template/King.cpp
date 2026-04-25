#include "King.h"

//C'est le constructeur!!! Je l'explique ici mais ca met automatiquement la couleur de la piece a la construction. Je pense que j'aurai pu le deplacer dans la classe de base mais trop tard ca marche pareil pis ca me tente pas.
King::King(SDL_Renderer* renderer, GridPosition piecePosition, PieceColor color, int tileSize)
	: Piece(renderer, piecePosition, color, tileSize)
{
	LoadTexture("assets/king.png");
	if (color == Black) SetTint(50, 50, 50);
}

//Je override parce que le roi c'est plus specifique.
std::vector<GridPosition> King::GetLegalMoves(std::function<Piece* (GridPosition)> getPieceAt, std::function<bool(GridPosition, PieceColor)> isTileAttacked)
{
	std::vector<GridPosition> legalMoves;
	for (GridPosition pos : GetAttackedSquares(getPieceAt)) {
		Piece* p = getPieceAt(pos);
		if (p != nullptr) {
			if (p->GetPieceColor() == color) continue;
		}
		if (isTileAttacked != nullptr && isTileAttacked(pos, GetPieceColor())) continue;
		legalMoves.push_back(pos);
	}
	return legalMoves;
}

//Ca retourne une liste des cases que la piece attaque.
std::vector<GridPosition> King::GetAttackedSquares(std::function<Piece* (GridPosition)> getPieceAt)
{
	GridPosition kingPosition = (GridPosition)GetPosition();
	return
	{
		{
			kingPosition + GridPosition(0,1),
			kingPosition + GridPosition(-1,0),
			kingPosition + GridPosition(0,-1),
			kingPosition + GridPosition(1,0),
			kingPosition + GridPosition(1,1),
			kingPosition + GridPosition(-1,1),
			kingPosition + GridPosition(-1,-1),
			kingPosition + GridPosition(1,-1),
		}
	};
}


