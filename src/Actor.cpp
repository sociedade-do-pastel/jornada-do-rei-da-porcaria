#include "../include/Actor.hpp"

#include "../include/Component.hpp"
#include "../include/Game.hpp"

Actor::Actor(Game* game)
    : m_state(State::Active), m_scale(1.0f), m_rotation(0.0f), m_game(game)
{
    m_game->addActor(this);
}

Actor::~Actor()
{
    m_game->removeActor(this);

    while (!m_components.empty())
        delete m_components.back();
}

void Actor::update()
{
    if (m_state == State::Active) {
        updateComponents();
        updateActor();
    }
}

void Actor::updateComponents()
{
    for (auto comp : m_components)
        comp->update();
}

void Actor::updateActor()
{
}

void Actor::processInput()
{
    if (m_state == State::Active) {
        for (auto& c : m_components)
            c->processInput();
    }
}

void Actor::addComponent(Component* component)
{
    int myOrder = component->getUpdateOrder();
    auto iter   = m_components.begin();
    for (; iter != m_components.end(); ++iter) {
        if (myOrder < (*iter)->getUpdateOrder())
            break;
    }

    m_components.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
    auto iter = std::find(m_components.begin(), m_components.end(), component);
    if (iter != m_components.end())
        m_components.erase(iter);
}
