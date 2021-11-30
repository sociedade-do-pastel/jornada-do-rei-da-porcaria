#pragma once

#include "AIComponent.hpp"
#include "Actor.hpp"
#include "GridComponent.hpp"
#include "SpriteComponent.hpp"
// forward declaration
class Game;

class Enemy : public Actor
{
public:
    Enemy(Game* game);
    virtual ~Enemy();

    void updateActor() override;

    // getters
    int getHP() const
    {
        return m_hp;
    }

    float getSpeed() const
    {
        return m_speed;
    }

    Rectangle getColRec() const override
    {
        Rectangle r;
        r.width  = m_spc->getTexWidth();
        r.height = m_spc->getTexHeight();
        r.x      = getPosition().x - r.width / 2.0f;
        r.y      = getPosition().y - r.height / 2.0f;

        return r;
    }

    // setters
    void setHP(int hp)
    {
        m_hp = hp;
    }

    void setSpeed(float speed)
    {
        m_speed = speed;
    }

    void setGrid(GridComponent* grid)
    {
        this->m_grid_component = grid;
    }

    void setAI(AIComponent* ai)
    {
        this->m_ai_component = ai;
    }

    void setKnockback(int time)
    {
        setSpeed(-1000 + getWeight() * 3);
        m_knockbackTime = time;
        m_inKnockback   = true;
    }

    void setWeight(float w)
    {
        m_weight = w;
    }

    // getters
    GridComponent* getGrid()
    {
        return m_grid_component;
    }

    AIComponent* getAI()
    {
        return m_ai_component;
    }

    float getWeight() const
    {
        return m_weight;
    }

protected:
    SpriteComponent* m_spc{nullptr};

private:
    int m_hp;
    int m_knockbackTime;
    bool m_inKnockback{false};
    float m_speed;
    float m_weight;
    GridComponent* m_grid_component{nullptr};
    AIComponent* m_ai_component{nullptr};
};
