#pragma once

#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <vector>

// forward declaration
class Component;
class Game;

class Actor
{
public:
    enum class State
    {
        Active,
        Paused,
        Dead
    };

    Actor(Game* game);
    virtual ~Actor();

    void update();
    void updateComponents();

    virtual void updateActor();
	virtual void processInput();

    // getters
    const Vector2& getPosition() const
    {
        return m_position;
    }

    float getScale() const
    {
        return m_scale;
    }

    const Vector2& getOgPosition() const
    {
        return m_ogPosition;
    }

    float getRotation() const
    {
        return m_rotation;
    }

    State getState() const
    {
        return m_state;
    }

    Game* getGame()
    {
        return m_game;
    }
	
    Vector2 GetForward() const
    {
        return Vector2{cosf(m_rotation), -sinf(m_rotation)};
    }

	virtual Rectangle getColRec() const
	{
		return {0, 0, 0, 0};
	}

    // setters
    void setPosition(const Vector2& pos)
    {
        m_position = pos;
    }

    void setScale(float scale)
    {
        m_scale = scale;
    }

    void setOgPosition(const Vector2& pos)
    {
        m_ogPosition = pos;
    }

    void setRotation(float rotation)
    {
        m_rotation = rotation;
    }

    void setState(State state)
    {
        m_state = state;
    }

    // component specific
    void addComponent(Component* component);
    void removeComponent(Component* component);

private:
    State m_state;

    Vector2 m_position;
    Vector2 m_ogPosition;
    float m_scale;
    float m_rotation;

    std::vector<Component*> m_components;
    Game* m_game;
};
