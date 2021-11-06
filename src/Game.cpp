#include "../include/Game.hpp"

#include <raylib.h>

#include "../include/Actor.hpp"
#include "../include/Player.hpp"
#include "../include/SpriteComponent.hpp"
#include "../include/World.hpp"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::initialize()
{
    // antialiasing
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(900, 900, "Jornada do rei da porcaria");

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

void Game::processInput()
{
    for (auto a : m_actors)
        a->processInput();
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

    EndDrawing();
}

void Game::loadData()
{
    new World(this, 16, 16);
    p = new Player(this);
    p->setPosition({GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});

    m_mouseTarget = LoadTexture("assets/alvo.png");
}

void Game::unloadData()
{
    UnloadTexture(m_mouseTarget);

    for (auto [key, val] : m_textures)
        UnloadTexture(val);

    while (!m_actors.empty())
        delete m_actors.back();
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
