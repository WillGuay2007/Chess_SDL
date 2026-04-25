#include "TransformStructs.h"

//Puisque Vector2 est avant la GridPosition, je m'assure de définir la fonction quand gridposition est valide, donc dans ce .cpp
Vector2::Vector2(GridPosition gridPos) : x(gridPos.column * TILE_SIZE), y(gridPos.row * TILE_SIZE) {}