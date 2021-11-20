#pragma once
#include <array>
#include <raylib.h>
#include <vector>
#include "Component.hpp"
#include "Grid.h"

class NodeWeights
{
public:
    struct node* referring_node{nullptr};
    NodeWeights* parent{nullptr};
    unsigned int h_cost{0};
    unsigned int g_cost{0};

    unsigned int getF_cost() const
    {
        return this->h_cost + this->g_cost;
    }
};

class GridComponent : public Component
{
public:
    GridComponent(Actor* owner);
    void init_actor_grid();
    void clean_actor_grid();
    NodeWeights* get_node_from_point(Vector2 point);
    NodeWeights* get_owner_node_from_point();
    unsigned int euclidean_distance(NodeWeights* node1, NodeWeights* node2);
    std::vector<NodeWeights*> get_neighbouring_nodes(NodeWeights* node);
    Vector2 get_translated(NodeWeights* og_pos)
    {
        node* temp = og_pos->referring_node;
        return {temp->screen_pos.x + offset.x, temp->screen_pos.y + offset.y};
    }

private:
    std::array<std::array<NodeWeights, NUMBER_OF_NODES_AXIS>,
               NUMBER_OF_NODES_AXIS>
        m_actors_grid;
    Vector2 offset{0};
};
