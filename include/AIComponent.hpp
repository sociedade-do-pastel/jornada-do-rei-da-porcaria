#pragma once
#include <raylib.h>
#include <stack>
#include "Actor.hpp"
#include "Component.hpp"
#include "GridComponent.hpp"

class AIComponent : public Component
{
public:
    AIComponent(Actor* owner, GridComponent* brother);
    void search_for_path();
    void update_heuristic();
    void backtrack_path(NodeWeights* start, NodeWeights* end);
    void update() override;

    void setTarget(Actor* target)
    {
        this->m_target = target;
    }

    std::stack<NodeWeights*>& getCurrentPath()
    {
        return m_current_path;
    }

private:
    Actor* m_target;
    NodeWeights* m_last_seen{nullptr};
    GridComponent* brother;
    std::stack<NodeWeights*> m_current_path;
};
