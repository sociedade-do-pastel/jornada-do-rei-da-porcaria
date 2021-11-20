#include "../include/AIComponent.hpp"
#include "../include/Enemy.hpp"

#include <algorithm>
#include <iostream>
#include <raymath.h>

AIComponent::AIComponent(Actor* owner, GridComponent* brother)
    : Component{owner}, brother{brother}
{
}

void AIComponent::search_for_path()
{
    NodeWeights* s_node{brother->get_owner_node_from_point()};
    NodeWeights* e_node{
        brother->get_node_from_point(this->m_target->getPosition())};

    std::vector<NodeWeights*> open;
    std::vector<NodeWeights*> closed;
    open.push_back(s_node);

    while (!open.empty()) {
        NodeWeights* current{open.at(0)};
        for (std::vector<NodeWeights*>::iterator it = open.begin();
             it != open.end(); ++it) {
            const auto& c_f_cost{current->getF_cost()};
            const auto& o_f_cost{(*it)->getF_cost()};
            if (o_f_cost < c_f_cost
                || (o_f_cost == c_f_cost && (*it)->h_cost < current->h_cost)) {
                current = (*it);
            }
        }

        open.erase(std::remove(open.begin(), open.end(), current));
        closed.push_back(current);

        if (current == e_node) {
            backtrack_path(s_node, e_node);
            return;
        }

        for (NodeWeights* neigh : brother->get_neighbouring_nodes(current)) {

            if (neigh->referring_node->count == 0
                || std::find(closed.begin(), closed.end(), neigh)
                       != closed.end())
                continue;

            unsigned int new_cost
                = current->g_cost + brother->euclidean_distance(current, neigh);

            std::vector<NodeWeights*>::iterator neighit
                = std::find(open.begin(), open.end(), neigh);

            if (new_cost < neigh->g_cost || neighit == open.end()) {
                neigh->g_cost = new_cost;
                neigh->h_cost = brother->euclidean_distance(neigh, e_node);
                neigh->parent = current;
                if (neighit == open.end())
                    open.push_back(neigh);
            }
        }
    }
}

void AIComponent::backtrack_path(NodeWeights* s_node, NodeWeights* e_node)
{
    NodeWeights* current = e_node;

    m_current_path = {};
    while (current != s_node) {
        m_current_path.push(current);
        current = current->parent;
    }
}

void AIComponent::update()
{
    Vector2 curr_pos       = this->m_target->getPosition();
    NodeWeights* curr_node = brother->get_node_from_point(curr_pos);

    if (curr_node != m_last_seen) {
        this->search_for_path();
        m_last_seen = curr_node;
        brother->clean_actor_grid();
    }
}
