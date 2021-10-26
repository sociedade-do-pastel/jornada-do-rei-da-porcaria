#pragma once

#include <algorithm>
#include <memory>
#include <raylib.h>
#include <vector>

// forward declaration
class Actor;
class SpriteComponent;
class Player;

class Game
{
public:
    Game();
    virtual ~Game();

    bool initialize();
    void runLoop();
    void shutdown();

    void addActor(Actor* actor);
    void removeActor(Actor* actor);

    void addSprite(SpriteComponent* sprite);
    void removeSprite(SpriteComponent* sprite);

    // void addCollision(CollisionComponent* collision);
    // void removeCollision(CollisionComponent* collision);

private:
    void processInput();
    void updateGame();
    void generateOutput();
    void loadData();
    void unloadData();

    bool m_isRunning;
    bool m_updatingActors;

	Player* p{nullptr};

    std::vector<Actor*> m_actors;
    std::vector<Actor*> m_pendingActors;
    std::vector<SpriteComponent*> m_sprites;
};
