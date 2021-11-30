#include "../include/EndScreen.hpp"

#include "../include/Game.hpp"

EndScreen::EndScreen(Game* game, Outcome out) : Actor(game)
{
    if (out == Outcome::Victory)
        m_endText = "Victory";
    else
        m_endText = "Defeat";

    game->setEndScreen(this);
}

EndScreen::~EndScreen()
{
}

void EndScreen::drawEnd()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    auto off = MeasureText(m_endText.c_str(), 50);
    DrawText(m_endText.c_str(), GetScreenWidth() / 2.0f - off / 2.0f,
             GetScreenHeight() / 2.0f, 50, WHITE);

    auto quit = "(esc to quit)";
    off       = MeasureText(quit, 25);
    DrawText(quit, GetScreenWidth() / 2.0f - off / 2.0f,
             GetScreenHeight() / 2.0f + 60.0f, 25, WHITE);
}
