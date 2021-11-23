#pragma once
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

    void setFlying(bool flying)
    {
      this->flying = flying;
    }

private:
    // current target (usually the only player that exists)
    Actor* m_target;
    // means that our owner is a flying mob
    bool flying{false};
    // where our target was last seen
    NodeWeights* m_last_seen{nullptr};
    GridComponent* brother;
    std::stack<NodeWeights*> m_current_path;
};
