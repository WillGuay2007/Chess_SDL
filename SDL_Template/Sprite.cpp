#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, int x, int y, int w, int h)
	: m_Texture(nullptr)
	, m_Rect(SDL_Rect())
	, m_renderer(renderer)
{
	m_Rect.x = x;
	m_Rect.y = y;
	m_Rect.w = w;
	m_Rect.h = h;
}

Sprite::Sprite(SDL_Renderer* renderer, GridPosition gridPos, Size size)
	: m_Texture(nullptr)
	, m_Rect(SDL_Rect())
	, m_renderer(renderer)
{
	SetSize(size);
	SetGridPositionCenter(gridPos);
}

Sprite::Sprite(SDL_Renderer* renderer, Vector2 pos, Size size)
	: m_Texture(nullptr)
	, m_Rect(SDL_Rect())
	, m_renderer(renderer)
{
	SetSize(size);
	SetPosition(pos);
}


Sprite::~Sprite()
{
	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}
}

bool Sprite::LoadTexture(const std::string& filename)
{
	m_Texture = IMG_LoadTexture(m_renderer, filename.c_str());
	if (m_Texture == nullptr)
	{
		SDL_Log("Error loading texture %s", filename.c_str());
		return false;
	}

	return true;
}

void Sprite::Draw()
{
	SDL_RenderCopyEx(m_renderer, m_Texture, nullptr, &m_Rect, 0.0, nullptr, SDL_FLIP_NONE);
}