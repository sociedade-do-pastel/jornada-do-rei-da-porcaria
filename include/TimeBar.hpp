#pragma once

#include "Actor.hpp"

class TimeBar : public Actor
{
public:
    TimeBar(Game* game, float duration);
    virtual ~TimeBar();

	void updateActor() override;
	void drawBar();

	// getters
	float getDuration() const
	{
		return m_duration;
	}

	// setters
	void setDuration(float d)
	{
		m_duration = d;
	}

private:
	float m_duration;
	float m_timePassed;

	Texture2D m_texture;
};

