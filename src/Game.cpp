#include "../include/Game.hpp"

#include <raylib.h>

#include "../include/Actor.hpp"
#include "../include/EndScreen.hpp"
#include "../include/LifeHUD.hpp"
#include "../include/Orc.hpp"
#include "../include/Player.hpp"
#include "../include/SoundManager.hpp"
#include "../include/SpriteComponent.hpp"
#include "../include/Tile.hpp"
#include "../include/TimeBar.hpp"
#include "../include/World.hpp"

Game::Game(int difficulty) : m_difficulty(difficulty)
{
}

Game::~Game()
{
}

bool Game::initialize()
{
    // antialiasing
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1000, 900, "Jornada do rei da porcaria");
    SetWindowIcon(LoadImage("assets/cabecao.png"));

    SetTargetFPS(60);
    HideCursor();

    loadData();

    return IsWindowReady();
}

void Game::runLoop()
{
    while (!WindowShouldClose()) {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::shutdown()
{
    unloadData();
    CloseWindow();
}

void Game::addActor(Actor* actor)
{
    if (m_updatingActors)
        m_pendingActors.emplace_back(actor);
    else
        m_actors.emplace_back(actor);
}

void Game::removeActor(Actor* actor)
{
    auto iter
        = std::find(m_pendingActors.begin(), m_pendingActors.end(), actor);

    if (iter != m_pendingActors.end()) {
        std::iter_swap(iter, m_pendingActors.end() - 1);
        m_pendingActors.pop_back();
    }

    iter = std::find(m_actors.begin(), m_actors.end(), actor);
    if (iter != m_actors.end()) {
        std::iter_swap(iter, m_actors.end() - 1);
        m_actors.pop_back();
    }
}

void Game::addSprite(SpriteComponent* sprite)
{
    int myDrawOrder = sprite->getDrawOrder();

    auto iter = m_sprites.begin();
    for (; iter != m_sprites.end(); ++iter) {
        if (myDrawOrder < (*iter)->getDrawOrder())
            break;
    }

    m_sprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent* sprite)
{
    auto iter = std::find(m_sprites.begin(), m_sprites.end(), sprite);
    m_sprites.erase(iter);
}

// void Game::addCollision(CollisionComponent* collision)
// {
// }

// void Game::removeCollision(CollisionComponent* collision)
// {
// }

void Game::addEnemy(Enemy* enemy)
{
    m_enemies.push_back(enemy);
}

void Game::removeEnemy(Enemy* enemy)
{
    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(),
                                   [enemy](auto& e) { return e == enemy; }),
                    m_enemies.end());
}

void Game::processInput()
{
    for (auto a : m_actors)
        a->processInput();

    if (IsKeyPressed(KEY_P) && m_isRunning) {
        m_smanager->add_sound("pare.ogg");
        togglePause();
    }
}

void Game::updateGame()
{
    // Update all actors
    m_updatingActors = true;
    for (auto actor : m_actors)
        actor->update();
    m_updatingActors = false;

    // Move any pending actors to mActors
    for (auto pending : m_pendingActors)
        m_actors.emplace_back(pending);
    m_pendingActors.clear();

    // Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;
    for (auto actor : m_actors) {
        if (actor->getState() == Actor::State::Dead)
            deadActors.emplace_back(actor);
    }

    // Delete dead actors (which removes them from mActors)
    for (auto actor : deadActors)
        delete actor;

    if (m_invincibilityTime != 0 && !m_gameIsPaused) {
        --m_invincibilityTime;
        if (m_invincibilityTime == 0)
            deactivateDamageInvinsibility();
    }
}

void Game::generateOutput()
{
    BeginDrawing();

    ClearBackground(BLACK);

    for (auto sprite : m_sprites)
        sprite->draw();

    // DrawLineV(p->getPosition(), GetMousePosition(), RED);

    DrawTextureV(
        m_mouseTarget,
        Vector2Subtract(GetMousePosition(), {m_mouseTarget.width / 2.0f,
                                             m_mouseTarget.height / 2.0f}),
        WHITE);

    m_timeBar->drawBar();
    m_lifeHUD->drawHP(m_player->getHP());

    if (m_gameIsPaused && m_isRunning) {
        auto off = MeasureText("Game is paused", 50);
        DrawText("Game is paused", GetScreenWidth() / 2.0f - off / 2.0f,
                 GetScreenHeight() / 2.0f, 50, WHITE);
    }

    if (m_endScreen != nullptr)
        m_endScreen->drawEnd();

    EndDrawing();
}

void Game::loadData()
{
    m_isRunning    = true;
    m_gameIsPaused = false;
    m_runningTime  = 180;

    /* 50, 50 refer to the offset in relation to the top-left corner of our
   window */
    m_worldp  = new World(this, 116, 50);
    m_player  = new Player(this);
    m_timeBar = new TimeBar(this, m_runningTime);
    m_lifeHUD = new LifeHUD(this);

    m_player->setPosition({GetScreenWidth() / 2.0f, GetScreenWidth() / 2.0f});

    m_mouseTarget = LoadTexture("assets/alvo.png");

    m_timeBar->setPosition({m_worldp->get_top_left().x, 20});

    m_lifeHUD->setPosition({30, 50});

    this->m_smanager = new SoundManager(this);
}

void Game::unloadData()
{
    UnloadTexture(m_mouseTarget);

    for (auto [key, val] : m_textures)
        UnloadTexture(val);

    while (!m_actors.empty())
        delete m_actors.back();
}

void Game::togglePause()
{
    m_gameIsPaused = !m_gameIsPaused;
    auto a
        = m_gameIsPaused == true ? Actor::State::Paused : Actor::State::Active;

    for (auto& f : getEnemies())
        f->setState(a);

    for (auto& f : getSpawnTiles())
        f->setState(a);

    for (auto& f : getCollisionTiles())
        f->setState(a);

    m_timeBar->setState(a);

    m_player->setState(a);
}

Texture& Game::getTexture(std::string name)
{
    auto t = m_textures.find(name);

    if (t != m_textures.end())
        return t->second;

    std::string target = "assets/" + name;
    m_textures[name]   = LoadTexture(target.c_str());
    return m_textures[name];
}

void Game::activateDamageInvinsibility()
{
    for (auto& f : getEnemies())
        f->setState(Actor::State::Paused);

    for (auto& f : getSpawnTiles())
        f->setState(Actor::State::Paused);

    m_timeBar->setState(Actor::State::Paused);

    m_player->setTakeDamage(false);
    m_invincibilityTime = 180;
}

void Game::deactivateDamageInvinsibility()
{
    for (auto& f : getEnemies())
        f->setState(Actor::State::Active);

    for (auto& f : getSpawnTiles())
        f->setState(Actor::State::Active);

    m_player->setTakeDamage(true);
    m_timeBar->setState(Actor::State::Active);
}
