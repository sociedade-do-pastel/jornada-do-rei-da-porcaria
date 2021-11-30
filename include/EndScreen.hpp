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

	void drawEnd();

private:
	std::string m_endText;
};
