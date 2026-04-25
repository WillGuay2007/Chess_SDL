#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "King.h"

//c'est le constructeur
Board::Board(SDL_Renderer* renderer)
	: m_Renderer(renderer)
	, m_selectedPiece(nullptr)
{
	InitTiles();
}

//Ca detruit tout les tuiles
Board::~Board()
{
	for (auto rowVector : m_tiles) for (Tile* tile : rowVector) {
		delete tile;
		//tile = nullptr; pas besoin parce que c'est une copie. De toute facon, les seules references que j'avais vers les tiles c'est a partir du vecteur.
	}
}

//Ca initialise les tuiles.
void Board::InitTiles()
{
	//Ici, je peut pas prendre l'itérateur puisque j'ai besoin des index
	for (int column = 0; column < BOARD_DIMENSIONS; column++)
	{
		m_tiles.push_back(std::vector<Tile*>());
		for (int row = 0; row < BOARD_DIMENSIONS; row++)
		{
			m_tiles[column].push_back(new Tile(m_Renderer, Vector2(row * TILE_SIZE, column * TILE_SIZE)));
		}
	}
}

//C'est principalement utilise comme lambda pour donner aux pieces vu que je veut pas trop de couplage entre board et pieces
Piece* Board::GetPieceAt(GridPosition pos) {
	if (!IsPositionInBounds(pos)) return nullptr;
	return GetTile(pos)->GetOccupyingPiece();
}

//Ca dessine le board
void Board::Draw()
{
	//J'utilise un itérateur parce que ca me permet de moins avoir de lignes de code
	//Dessiner les tuiles en premier
	for (auto rowVector : m_tiles) for (Tile* tile : rowVector) tile->Draw();

	//Pieces en deuxieme.
	for (auto rowVector : m_tiles) for (Tile* tile : rowVector)
	{
		Piece* pieceToDraw = tile->GetOccupyingPiece();
		if (pieceToDraw != nullptr) pieceToDraw->Draw();
	}

}

//Ca verifie si la grid position est dans le grid ou pas.
bool Board::IsPositionInBounds(GridPosition pos) {
	return (pos.row >= 0 && pos.row < BOARD_DIMENSIONS && pos.column >= 0 && pos.column < BOARD_DIMENSIONS);
}

//Garder les tuiles qui sont dans le grid et enlever ceux qui sont hors.
std::vector<GridPosition> Board::FilterOutOfBoundsTiles(std::vector<GridPosition> moves) {
	std::vector<GridPosition> validTiles;
	for (GridPosition pos : moves) {
		if (IsPositionInBounds(pos)) validTiles.push_back(pos);
	}
	return validTiles;
}

//Ca va deplacer la piece avec ton curseur
void Board::MouseMotion(Vector2 mousePos)
{
	if (m_selectedPiece != nullptr) m_selectedPiece->SetPositionCenter(mousePos);
}

//Ca reset toutes les cases qui sont highlight.
void Board::ResetHighlights() {
	for (auto rowVector : m_tiles) for (Tile* tile : rowVector) tile->ResetTexture();
}

//Ca trouve la position du roi en iterant sur tout les pieces. C'est pas tres performant mais ca marche
GridPosition Board::FindKingPosition(PieceColor requiredColor)
{
	for (auto rowVector : m_tiles) {
		for (Tile* tile : rowVector) {
			Piece* piece = tile->GetOccupyingPiece();
			if (piece == nullptr) continue;

			if (dynamic_cast<King*>(piece) && piece->GetPieceColor() == requiredColor) return tile->GetPosition();
		}
	}
	SDL_assert(false && "King not found."); //Normalement, cette ligne devrait jamais arriver. c'est pour ca que je fais assert. Pour donner un warning.
	return { -1,-1 };
}

//C'est utilise avec MouseButtonDown et ca selectionne une piece et met ses highlights
void Board::SelectPiece(Vector2 mousePos) {
	Tile* clickedTile = GetTile(mousePos);
	Piece* clickedPiece = clickedTile->GetOccupyingPiece();

	//Si la tuile cliquée a pas de piece, alors on enleve le highlight et on select rien.
	if (clickedPiece == nullptr) {
		ResetHighlights();
		m_selectedPiece = nullptr; //Mon choix de design.
		return;
	}

	//Si la piece sur la tuile cliquée existe, alors on set le highlight et on update la piece et la position de debut de drag
	ResetHighlights();
	m_selectedPiece = clickedPiece;
	m_dragOrigin = clickedPiece->GetPosition();
	SetLegalMovesHighlight(clickedPiece);
	GetTile(clickedPiece->GetPosition())->SetSelectionColor();
}

//C'est utilise avec MouseButtonUp pour le deplacement de piece
bool Board::DropPiece(Vector2 mousePos) {
	if (m_selectedPiece == nullptr) return false;
	Tile* releaseTile = GetTile(mousePos);
	Piece* clickedPiece = releaseTile->GetOccupyingPiece();

	//Si on relache sur une tuile highlight, on deplace la piece (avec capture potentielle)
	if (releaseTile->IsHighlighted()) {
		m_selectedPiece->SetPosition(m_dragOrigin);
		MovePieceAndCapture(m_selectedPiece, releaseTile->GetPosition());
		ResetHighlights();
		m_selectedPiece = nullptr;
		return true;
	}
	m_selectedPiece->SetPosition(m_dragOrigin);
	m_selectedPiece = nullptr;
	return false;
}

//Prevu pour etre utilise avec SimulateMove.
void Board::UndoMove(Piece* movedPiece, GridPosition originalPos, Piece* capturedPiece, GridPosition captureLocation)
{
	//Remettre la piece deplacee a sa tuile originale
	GetTile(movedPiece->GetPosition())->RemoveOccupyingPiece();
	movedPiece->SetPosition(originalPos);
	Tile* originalTile = GetTile(originalPos);
	originalTile->AssignPiece(movedPiece);

	if (capturedPiece == nullptr) return;

	Tile* captureLocationTile = GetTile(captureLocation);
	captureLocationTile->AssignPiece(capturedPiece);

}

//C'est pareil que move and capture sauf que on delete pas la piece. La piece est retournée pour etre utilisée dans undo move
Piece* Board::SimulateMove(Piece* pieceToMove, GridPosition destination)
{
	GetTile(pieceToMove->GetPosition())->RemoveOccupyingPiece();
	Tile* destinationTile = GetTile(destination);
	pieceToMove->SetPosition(destination);
	Piece* pieceToCapture = destinationTile->GetOccupyingPiece();
	if (pieceToCapture != nullptr) {
		destinationTile->RemoveOccupyingPiece();
	}
	destinationTile->AssignPiece(pieceToMove);
	return pieceToCapture;
}

//C'est le mouvement par defaut. Soit ca bouge, soit ca bouge et ca capture. c'est ce qui gere les moves
void Board::MovePieceAndCapture(Piece* pieceToMove, GridPosition destination)
{
	GetTile(pieceToMove->GetPosition())->RemoveOccupyingPiece();
	Tile* destinationTile = GetTile(destination);
	pieceToMove->SetPosition(destination);
	Piece* pieceToCapture = destinationTile->GetOccupyingPiece();
	if (pieceToCapture != nullptr) {
		destinationTile->RemoveOccupyingPiece();
		delete pieceToCapture;
		pieceToCapture = nullptr;
	}
	destinationTile->AssignPiece(pieceToMove);
}

//Ca assigne la piece a une tuile.
void Board::AssignPiece(GridPosition pos, Piece* piece)
{
	Tile* tile = GetTile(pos);
	if (tile->GetOccupyingPiece() != nullptr) {
		std::cout << "A piece is already occupying the square. Assign failed.\n";
	}
	tile->AssignPiece(piece);
}

//Ca verifie si la gris position selectionnee est attaquee par une piece adverse. ca ignore nos allies
bool Board::IsSquareAttacked(GridPosition pos, PieceColor friendlyColor) {
	//C'est une lambda qu'on passe a la piece pour eviter du couplage.
	auto getPieceAt = [this](GridPosition pos) { return GetPieceAt(pos); };

	if (!IsPositionInBounds(pos)) return true; //Dans mon cas, je décide de considerer une place out of bounds comme attaquée.
	//Je check toutes les pieces ennemies et je check tout les tuiles quils attaquent. Si une de ces tuiles match, on retourne true. Sinon false.
	for (auto rowVector : m_tiles) for (Tile* tile : rowVector) {
		Piece* p = tile->GetOccupyingPiece();
		if (p == nullptr) continue;
		if (p->GetPieceColor() == friendlyColor) continue;
		for (GridPosition _pos : p->GetAttackedSquares(getPieceAt)) {
			if (_pos == pos) return true;
		}
	}
	return false;
}

//Ca set le highlight. Aussi, ca filtre d'avantage pour les clouages et les checks (Par exemple: bloquer le roi avec une piece)
void Board::SetLegalMovesHighlight(Piece* pieceToDisplay) {
	if (pieceToDisplay != nullptr) {
		auto getPieceAt = [this](GridPosition pos) { return GetPieceAt(pos); };

		auto isSquareAttacked = [this](GridPosition pos, PieceColor pieceColor) -> bool {
			return IsSquareAttacked(pos, pieceColor);
		};
		std::vector<GridPosition> legalMoves = pieceToDisplay->GetLegalMoves(getPieceAt, isSquareAttacked);

		legalMoves = FilterOutOfBoundsTiles(legalMoves);

		for (GridPosition move : legalMoves) {
			if (IsKingInCheckAfterMove(pieceToDisplay, move)) continue;
			Tile* tile = GetTile(move);
			tile->Highlight();
		}
	}
}

//Ca verifie si le roi est en échec apres un move. Cette fonction est utilisee avec simulate move et undo move.
bool Board::IsKingInCheckAfterMove(Piece* pieceToMove, GridPosition move) {
	GridPosition originalPos = pieceToMove->GetPosition();
	Piece* simulatedCapture = SimulateMove(pieceToMove, move);
	bool kingInCheck = IsSquareAttacked(FindKingPosition(pieceToMove->GetPieceColor()), pieceToMove->GetPieceColor());
	UndoMove(pieceToMove, originalPos, simulatedCapture, move);
	return kingInCheck;
}

//Ca verifie AU MOINS une des pieces de la couleur choisie peut bouger. Sinon, c'est echet et mat
bool Board::HasAnyLegalMove(PieceColor colorToCheck) {

	auto getPieceAt = [this](GridPosition pos) { return GetPieceAt(pos); };
	auto isSquareAttacked = [this](GridPosition pos, PieceColor pieceColor) -> bool {
		return IsSquareAttacked(pos, pieceColor);
	};

	for (auto rowVector : m_tiles) for (Tile* tile : rowVector) {
		Piece* pieceToCheck = tile->GetOccupyingPiece();
		if (pieceToCheck == nullptr || pieceToCheck->GetPieceColor() != colorToCheck) continue;

		std::vector<GridPosition> legalMoves = pieceToCheck->GetLegalMoves(getPieceAt, isSquareAttacked);
		legalMoves = FilterOutOfBoundsTiles(legalMoves);

		for (GridPosition move : legalMoves) {
			if (IsKingInCheckAfterMove(pieceToCheck, move)) continue;
			return true;
		}
	}
	return false;
}