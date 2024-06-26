#pragma once

#include <Config.hpp>
#include <objects/BaseObject.hpp>
#include <components/Damage.hpp>

class Bullet : public BaseObject, public Damage
{
private:
	int m_speed;
	float m_elapsedTime;

public:
	Bullet(float, SDL_Point);

	void Update(float) override;
};