#pragma once

#include <Config.hpp>
#include <objects/BaseObject.hpp>

class AnimatedObject : public BaseObject
{
private:
	int			m_maxFrame;
	int			m_currentFrame;
	float		m_timePerFrame;
	float		m_elapsedTime;

public:
	AnimatedObject() = default;
	AnimatedObject(int, float);

	void UpdateAnimation(float);
};