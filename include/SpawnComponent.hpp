#pragma once
#include <raylib.h>
#include "Component.hpp"

template <typename T> class SpawnComponent : public Component
{
public:
    /* Interval should be in seconds */
    SpawnComponent(Actor* owner, double interval)
        : Component{owner}, m_spawnInterval{interval},
	  m_lastTimeRegistered{GetTime()}
    {
    }

    virtual ~SpawnComponent()
    {
    }
  
    void update()
    {
        double current_time{GetTime()};
	
        if ((current_time - m_lastTimeRegistered) >= m_spawnInterval) {
            spawnActor();
            m_lastTimeRegistered = current_time;
        }
    }

    void spawnActor()
    {
      /* make sure that the actor you're trying to spawn has the method
	 ``setPosition'' */
        T* actor_to_spawn{new T(this->m_owner->getGame())};
        actor_to_spawn->setPosition(this->m_owner->getPosition());
    }

    // getters
    double getSpawnInterval() const
    {
        return m_spawnInterval;
    }

    double getLastTimeRegistered() const
    {
        return m_lastTimeRegistered;
    }

    // setters
    double setSpawnInterval(const double new_interval)
    {
        this->m_spawnInterval = new_interval;
    }

private:
  /* time (in seconds) between our spawns */
  double m_spawnInterval{0};
  
  /* time since our last spawn */
  double m_lastTimeRegistered{0};
};
