#pragma once

#include <Config.hpp>
#include <components/HP.hpp>
#include <objects/AnimatedObject.hpp>

class Tower final : public AnimatedObject, public HP
{
private:
	SDL_Rect m_totalHP;
	SDL_Rect m_currentHP;
	float m_elapsedTime;

public:
	Tower();

	void Update(float) override;

	void Render(SDL_Renderer*) override;
};