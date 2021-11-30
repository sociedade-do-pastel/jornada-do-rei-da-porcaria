#pragma once

#include <algorithm>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Actor.hpp"
#include "Component.hpp"

template <typename T> class SpawnComponent : public Component
{
public:
    /* Runtime should be in seconds */
    SpawnComponent(Actor* owner, int levelTime)
        : Component{owner}, m_timePassed{0}
    {
        for (int i{0}; i < GetRandomValue(2, 8); ++i)
            m_spawnTimes.push_back(GetRandomValue(0, levelTime));

        std::sort(m_spawnTimes.begin(), m_spawnTimes.end());
    }

    virtual ~SpawnComponent()
    {
    }

    void update()
    {
        if (getOwner()->getState() == Actor::State::Paused)
            return;
		
        ++m_timePassed;

        if (!m_spawnTimes.empty() && m_timePassed / 60 >= m_spawnTimes[0]) {
            spawnActor();
            m_spawnTimes.erase(m_spawnTimes.begin());
        }
    }

    void spawnActor()
    {
        /* make sure that the actor you're trying to spawn has the method
       ``setPosition'' */
        T* actor_to_spawn{new T(this->m_owner->getGame())};

        actor_to_spawn->setPosition(m_owner->getPosition());
    }

private:
    std::vector<int> m_spawnTimes;
    int m_timePassed;
};
