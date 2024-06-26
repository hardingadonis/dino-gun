#include <objects/Player.hpp>
#include <types/Vector2f.hpp>
#include <Resource.hpp>

Player::Player() :
	AnimatedObject(6, 0.1f),
	m_speed(200),
	m_isShotable(true),
	m_elapsedTime(0.f)
{
	this->m_texture = Resource::TX_PLAYER;
	this->m_rectSrc->w = 72;
	this->m_rectSrc->h = 72;

	this->m_rectDst->w = 72;
	this->m_rectDst->h = 72;

	this->m_rectCollision->w = this->m_rectCollision->h = 50;
	this->m_rectCollision->x = this->m_rectCollision->y = 11;

	this->SetOrigin({ 100, 100 });

	this->m_gun = new Gun();
}

void Player::Update(float delta)
{
	this->m_elapsedTime += delta;

	if (this->m_elapsedTime > 0.3f)
	{
		this->m_isShotable = true;
	}

	this->UpdateAnimation(delta);

	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	Vector2f vector;

	if (keyboardState[SDL_SCANCODE_A])
	{
		this->SetFlipH(true);
		vector.x = -1.f;
	}

	if (keyboardState[SDL_SCANCODE_D])
	{
		this->SetFlipH(false);
		vector.x = 1.f;
	}

	if (keyboardState[SDL_SCANCODE_W])
	{
		vector.y = -1.f;
	}

	if (keyboardState[SDL_SCANCODE_S])
	{
		vector.y = 1.f;
	}

	vector = vector.Normalize();
	this->Move(vector * (delta * this->m_speed));

	int xOffset = this->m_rectDst->w / 2;
	int yOffset = this->m_rectDst->h / 2;

	if (this->m_origin->x < xOffset)
	{
		this->SetOrigin({ xOffset, this->m_origin->y });
	}

	if (this->m_origin->x > WINDOW_WIDTH - xOffset)
	{
		this->SetOrigin({ WINDOW_WIDTH - xOffset, this->m_origin->y });
	}

	if (this->m_origin->y < yOffset)
	{
		this->SetOrigin({ this->m_origin->x, yOffset });
	}

	if (this->m_origin->y > WINDOW_HEIGHT - yOffset)
	{
		this->SetOrigin({ this->m_origin->x, WINDOW_HEIGHT - yOffset });
	}

	this->m_gun->SetOrigin(this->GetOrigin());
	this->m_gun->Update(delta);
}

void Player::Render(SDL_Renderer* renderer)
{
	BaseObject::Render(renderer);

	this->m_gun->Render(renderer);
}

bool Player::IsShotable() const
{
	return this->m_isShotable;
}

Bullet* Player::Shot()
{
	this->m_isShotable = false;
	this->m_elapsedTime = 0.f;

	return new Bullet(this->m_gun->GetAngle(), this->GetOrigin());
}