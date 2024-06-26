#pragma once

#include <Config.hpp>
#include <components/Damage.hpp>
#include <components/HP.hpp>
#include <objects/AnimatedObject.hpp>

enum class ThreatState {
	ATTACK,
	DEATH,
	WALK
};

class Threat : public AnimatedObject, public HP, public Damage
{
protected:
	ThreatState m_state;
	int m_speed;

	SDL_Texture* m_attackTex;
	SDL_Texture* m_deathTex;
	SDL_Texture* m_walkTex;

	SDL_Rect m_totalHP;
	SDL_Rect m_currentHP;

	float m_elapsedTime;
	bool m_isAttackable;

public:
	Threat(SDL_Texture*, SDL_Texture*, SDL_Texture*, int, int, int);

	void SetState(ThreatState state);

	ThreatState GetState() const;

	void Update(float) override;
	void Render(SDL_Renderer*) override;

	bool IsAttackable() const;
	int Attack();

	virtual int Score() = 0;

	static Threat* Generate();
};