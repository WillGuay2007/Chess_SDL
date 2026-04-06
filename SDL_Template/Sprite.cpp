#include "Sprite.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, int x, int y, int w, int h)
	: m_texture(nullptr)
	, m_Rect(SDL_Rect())
	, m_renderer(renderer)
{
	m_Rect.x = x;
	m_Rect.y = y;
	m_Rect.w = w;
	m_Rect.h = h;
}

Sprite::Sprite(SDL_Renderer* renderer, GridPosition gridPos, Size size, int tileSize)
	: m_texture(nullptr)
	, m_Rect(SDL_Rect())
	, m_renderer(renderer)
{
	SetSize(size);
	SetPosition(gridPos * tileSize);
}

Sprite::Sprite(SDL_Renderer* renderer, Vector2 pos, Size size)
	: m_texture(nullptr)
	, m_Rect(SDL_Rect())
	, m_renderer(renderer)
{
	SetSize(size);
	SetPosition(pos);
}


Sprite::~Sprite()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

bool Sprite::LoadTexture(const std::string& filename)
{
	m_texture = IMG_LoadTexture(m_renderer, filename.c_str());
	if (m_texture == nullptr)
	{
		SDL_Log("Error loading texture %s", filename.c_str());
		return false;
	}

	return true;
}

void Sprite::Draw()
{
	if (m_texture == nullptr) {
		std::cout << "Sprite could not be drawn. Please provide a texture.\n";
		return;
	}
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &m_Rect, 0.0, nullptr, SDL_FLIP_NONE);
}