#include "../include/TimeBar.hpp"

#include "../include/EndScreen.hpp"
#include "../include/Game.hpp"

TimeBar::TimeBar(Game* game, float duration)
    : Actor(game), m_duration(duration * 60), m_timePassed(0)
{
    m_texture = getGame()->getTexture("relojooj.png");
}

TimeBar::~TimeBar()
{
}

void TimeBar::updateActor()
{
    if (getState() != Actor::State::Paused)
        ++m_timePassed;

    if (m_timePassed >= m_duration)
        new EndScreen(getGame(), EndScreen::Outcome::Victory);
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

    DrawTexture(m_texture, getPosition().x, getPosition().y - 10, WHITE);
    DrawRectangle(getPosition().x + 40, getPosition().y, 728 - 728 * percentage,
                  20, c);
}
