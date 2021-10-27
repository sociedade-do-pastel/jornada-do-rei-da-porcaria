#pragma once

// forward declaration
class Actor;

class Component
{
public:
    Component(Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void update();
	virtual void processInput();

    // getters
    int getUpdateOrder() const
    {
        return m_updateOrder;
    }

protected:
    Actor* m_owner;
    int m_updateOrder;
};
