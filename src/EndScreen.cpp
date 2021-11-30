#include "../include/EndScreen.hpp"

#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/SoundManager.hpp"

EndScreen::EndScreen(Game* game, Outcome out) : Actor(game)
{
    if (out == Outcome::Victory) {
        m_endText = "Victory";
        game->getPlayer()->setEndFrame(14);
        game->getSoundManager()->add_sound("resident-door.ogg");
    }
    else {
        m_endText = "Defeat";
        game->getPlayer()->setEndFrame(15);
    }

    game->setEndScreen(this);
    game->getPlayer()->setPosition(
        {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});

    game->togglePause();
    game->setRunning(false);
}

EndScreen::~EndScreen()
{
}

void EndScreen::updateActor()
{
    ++m_offset;
}

void EndScreen::drawEnd()
{
    DrawRectangle(0, 0, GetScreenWidth(), m_offset, BLACK);
    DrawRectangle(0, 0, m_offset, GetScreenHeight(), BLACK);
    DrawRectangle(0, GetScreenHeight() - m_offset, GetScreenWidth(), m_offset,
                  BLACK);
    DrawRectangle(GetScreenWidth() - m_offset, 0, m_offset, GetScreenHeight(),
                  BLACK);

    auto off = MeasureText(m_endText.c_str(), 50);
    DrawText(m_endText.c_str(), GetScreenWidth() / 2.0f - off / 2.0f,
             GetScreenHeight() / 2.0f + 100.0f, 50, WHITE);

    auto quit = "(esc to quit)";
    off       = MeasureText(quit, 25);
    DrawText(quit, GetScreenWidth() / 2.0f - off / 2.0f,
             GetScreenHeight() / 2.0f + 160.0f, 25, WHITE);
}
