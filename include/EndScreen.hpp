#pragma once

#include <string>

#include "Actor.hpp"

class EndScreen : public Actor
{
public:
	enum class Outcome
    {
        Victory,
        Defeat
    };
	
    EndScreen(Game* game, Outcome out);
    virtual ~EndScreen();

	void updateActor() override;
	void drawEnd();

private:
	std::string m_endText;
	int m_offset{0};
};
