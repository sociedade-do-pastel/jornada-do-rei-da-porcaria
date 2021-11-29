#include "../include/TimeBar.hpp"

TimeBar::TimeBar(Game* game, float duration)
    : Actor(game), m_duration(duration * 60), m_timePassed(0)
{
}

TimeBar::~TimeBar()
{
}

void TimeBar::updateActor()
{
    ++m_timePassed;
}

void TimeBar::drawBar()
{
    float percentage = m_timePassed / m_duration;
    Color c;

    if (percentage <= 0.25)
        c = GREEN;
    else if (percentage <= 0.75)
        c = YELLOW;
    else
        c = RED;

    DrawRectangle(getPosition().x, getPosition().y, 768 - 768 * percentage, 20,
                  c);
}
