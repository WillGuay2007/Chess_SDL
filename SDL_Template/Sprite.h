#pragma once
#include "SDL_image.h"
#include <string>
#include "TransformStructs.h"
#include "GameSettings.h"

class Sprite
{
public:
	
	Sprite(SDL_Renderer* renderer, int a_X, int a_Y, int a_W, int a_H);
	Sprite(SDL_Renderer* renderer, GridPosition gridPos, Size size);
	Sprite(SDL_Renderer* renderer, Vector2 pos, Size size);
	virtual ~Sprite();

	bool LoadTexture(const std::string& filename);

	void Draw();

	void SetPosition(const Vector2 newPosition) { m_Rect.x = newPosition.x; m_Rect.y = newPosition.y; }
	void SetPositionCenter(const Vector2 newPosition) { m_Rect.x = newPosition.x - m_Rect.w / 2; m_Rect.y = newPosition.y - m_Rect.h / 2; }
	void SetGridPosition(const GridPosition newGridPosition) { SetPosition(newGridPosition * TILE_SIZE); }
	void SetGridPositionCenter(const GridPosition newGridPosition) { SetPositionCenter(newGridPosition * TILE_SIZE); }
	void Translate(Vector2 offset) { m_Rect.x += offset.x; m_Rect.y += offset.y; }

	void SetSize(Size newSize) { m_Rect.w = newSize.width; m_Rect.h = newSize.height; }

	Vector2 GetPosition() { return Vector2(m_Rect.x, m_Rect.y); }
	Vector2 GetCenterPosition() { return Vector2(m_Rect.x + m_Rect.w / 2, m_Rect.y + m_Rect.h / 2); }
	GridPosition GetGridPosition() { return GridPosition(m_Rect.x / TILE_SIZE, m_Rect.y / TILE_SIZE); }
	Size GetSize() { return Size(m_Rect.w, m_Rect.h); }

private:
	SDL_Renderer* m_renderer;
	SDL_Rect m_Rect;
	SDL_Texture* m_Texture;
};

