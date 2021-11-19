#pragma once

#include <algorithm>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <unordered_map>
#include <vector>

// forward declaration
class Actor;
class SpriteComponent;
class Player;
class World;
class Enemy;
class Tile;

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

    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);

    Texture& getTexture(std::string name);
    // void addCollision(CollisionComponent* collision);
    // void removeCollision(CollisionComponent* collision);

    std::vector<Enemy*>& getEnemies()
    {
        return m_enemies;
    }

    std::vector<Tile*>& getCollisionTiles()
    {
        return this->m_collisionTiles;
    }

    World* getWorld()
    {
        return this->m_worldp;
    }

private:
    void processInput();
    void updateGame();
    void generateOutput();
    void loadData();
    void unloadData();

    bool m_isRunning;
    bool m_updatingActors;

    Player* p{nullptr};

    Texture m_mouseTarget;

    std::unordered_map<std::string, Texture> m_textures;

    std::vector<Actor*> m_actors;
    std::vector<Actor*> m_pendingActors;
    std::vector<SpriteComponent*> m_sprites;
    std::vector<Enemy*> m_enemies;
    std::vector<Tile*> m_collisionTiles;
    World* m_worldp{nullptr};
};
