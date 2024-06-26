#include <objects/Tower.hpp>
#include <Resource.hpp>

Tower::Tower() :
	AnimatedObject(11, 0.15f),
	HP(100),
	m_elapsedTime(0.f)
{
	this->m_texture = Resource::TX_MAP_TOWER;

	this->m_rectSrc->w = 100;
	this->m_rectSrc->h = 140;

	this->m_rectDst->w = 150;
	this->m_rectDst->h = 210;
	this->m_rectDst->x = (WINDOW_WIDTH - this->m_rectDst->w) / 2;
	this->m_rectDst->y = (WINDOW_HEIGHT - this->m_rectDst->h) / 2;

	this->m_rectCollision->w = 80;
	this->m_rectCollision->h = 130;
	this->m_rectCollision->x = this->m_rectDst->x + (this->m_rectDst->w - this->m_rectCollision->w) / 2;
	this->m_rectCollision->y = this->m_rectDst->y + (this->m_rectDst->h - this->m_rectCollision->h) / 2 + 30;

	this->m_totalHP.w = this->m_currentHP.w = WINDOW_WIDTH / 2;
	this->m_totalHP.h = this->m_currentHP.h = 5;
	this->m_totalHP.x = this->m_currentHP.x = (WINDOW_WIDTH - this->m_totalHP.w) / 2;
	this->m_totalHP.y = this->m_currentHP.y = 10;
}

void Tower::Update(float delta)
{
	this->m_elapsedTime += delta;

	if (this->m_elapsedTime > 5.f)
	{
		int tHP = this->GetCurrentHP() + 7;

		if (tHP <= this->GetMaxHP())
		{
			this->SetCurrentHP(tHP);
		}
		else
		{
			this->SetCurrentHP(this->GetMaxHP());
		}

		this->m_elapsedTime -= 5.f;
	}

	this->UpdateAnimation(delta);

	this->m_currentHP.w = (int)((float)this->GetCurrentHP() / (float)this->GetMaxHP() * this->m_totalHP.w);

	if (this->GetCurrentHP() <= 0)
	{
		this->m_isAlive = false;
	}
}

void Tower::Render(SDL_Renderer* renderer)
{
	BaseObject::Render(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &this->m_totalHP);

	if (this->GetCurrentHP() > 0)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &this->m_currentHP);
	}
}