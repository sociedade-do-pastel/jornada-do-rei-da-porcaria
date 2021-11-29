#pragma once
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include "Component.hpp"

template <typename T> class SpawnComponent : public Component
{
public:
    /* Runtime should be in seconds */
    SpawnComponent(Actor* owner, double runtime = 60, unsigned how_many = 10)
        : Component{owner}, m_runtime{runtime}, m_lastTimeRegistered{GetTime()},
          m_number_of_enemies{how_many}
    {
        this->m_interval = floor(m_runtime / how_many);
    }

    virtual ~SpawnComponent()
    {
    }

    void update()
    {
        double current_time{GetTime()};

        if (((current_time - m_lastTimeRegistered) >= m_interval)
            && m_number_of_enemies > 0) {
            spawnActor();
            m_lastTimeRegistered = current_time;
            --(this->m_number_of_enemies);
        }
    }

    void spawnActor()
    {
        /* make sure that the actor you're trying to spawn has the method
       ``setPosition'' */
        T* actor_to_spawn{new T(this->m_owner->getGame())};

        unsigned int tile_diam{
            this->m_owner->getGame()->getWorld()->get_tile_diameter()};

        Vector2 actor_center_pos{
            Vector2Add(this->m_owner->getPosition(),
                       (Vector2){(float)tile_diam, (float)tile_diam})};

        actor_to_spawn->setPosition(actor_center_pos);
    }

    // getters
    double getRuntime() const
    {
        return m_runtime;
    }

    double getLastTimeRegistered() const
    {
        return m_lastTimeRegistered;
    }

private:
    /* total time (in seconds) of our level */
    double m_runtime{0};

    /* time since our last spawn */
    double m_lastTimeRegistered{0};

    /* how many enemies should be spawned */
    unsigned m_number_of_enemies{0};

    /* interval between spawns */
    double m_interval{0};
};
