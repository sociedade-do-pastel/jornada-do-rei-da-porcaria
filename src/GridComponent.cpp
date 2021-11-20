#include "../include/GridComponent.hpp"
#include <raylib.h>
#include <raymath.h>
#include "../include/World.hpp"

GridComponent::GridComponent(Actor* owner) : Component{owner}
{
    init_actor_grid();
};

// get all the neighhbouring nodes by their index in the tilemap
//
// here we try to distinguish between 4 directions (orc behaviour)
// and 8 directions (dragon behaviour)
std::vector<NodeWeights*> GridComponent::get_neighbouring_nodes(
    NodeWeights* node, bool four_d)
{
    std::vector<NodeWeights*> neighbours;

    if (!four_d) {
        int og_j{node->referring_node->j};
        int og_i{node->referring_node->i};
        generate_neighbours_4d(neighbours, og_i, og_j);
    }
    else {
        int top_left_i{node->referring_node->i - 1};
        int top_left_j{node->referring_node->j - 1};
        generate_neighbours_8d(neighbours, top_left_i, top_left_j);
    }
    return neighbours;
}

// get all the 4 nodes that are neighbours of node i, j
void GridComponent::generate_neighbours_4d(
    std::vector<NodeWeights*>& neighbours, int i, int j)
{
    // push back the one on the right
    neighbours.push_back(&(m_actors_grid[i][j + 1]));
    // the one on the left
    neighbours.push_back(&(m_actors_grid[i][j - 1]));
    // the one at the top
    neighbours.push_back(&(m_actors_grid[i - 1][j]));
    // the one at the bottom
    neighbours.push_back(&(m_actors_grid[i + 1][j]));
}

// just like the above, but start counting from the top left
// and get 8 of them instead
void GridComponent::generate_neighbours_8d(
    std::vector<NodeWeights*>& neighbours, int top_left_i, int top_left_j)
{

    for (int i{top_left_i}; i <= top_left_i + 2; ++i) {
        for (int j{top_left_j}; j <= top_left_j + 2; ++j) {
            if ((i < 0 || i > NUMBER_OF_NODES_AXIS - 1 || j < 0
                 || j > NUMBER_OF_NODES_AXIS - 1)
                || (i == top_left_i + 1 && j == top_left_j + 1))
                continue;
            neighbours.push_back(&(m_actors_grid[i][j]));
        }
    }
}

// initialize our grid by pointing all ``NodeWeights'' to their original,
// global node
//
// this way we can assign different weights to each global node while
// not getting in the way of another AI component
void GridComponent::init_actor_grid()
{
    World* cur_world  = this->m_owner->getGame()->getWorld();
    Grid* global_grid = cur_world->get_main_grid();
    for (int i{0}; i < NUMBER_OF_NODES_AXIS; ++i) {
        for (int j{0}; j < NUMBER_OF_NODES_AXIS; ++j) {
            m_actors_grid[i][j].referring_node
                = &(global_grid->world[cur_world->get_curr_map()][i][j]);
        }
    }
    this->offset = cur_world->get_top_left();
}

// zeroes all weights given for each node, while erasing their ``parent''
// pointers
void GridComponent::clean_actor_grid()
{
    Grid* global_grid = this->m_owner->getGame()->getWorld()->get_main_grid();
    for (int i{0}; i < NUMBER_OF_NODES_AXIS; ++i) {
        for (int j{0}; j < NUMBER_OF_NODES_AXIS; ++j) {
            m_actors_grid[j][i].g_cost = 0;
            m_actors_grid[j][i].h_cost = 0;
            m_actors_grid[j][i].parent = nullptr;
        }
    }
}

// gets the euclidean distance between two nodes (in order to get the h cost
// between them)
unsigned int GridComponent::euclidean_distance(NodeWeights* begin,
                                               NodeWeights* end)
{
    Vector2 end_node_pos       = this->get_translated(end);
    Vector2 beginning_node_pos = this->get_translated(begin);

    return (unsigned int)Vector2Distance(beginning_node_pos, end_node_pos);
}

// get the node in which the owner of this component is standing on
NodeWeights* GridComponent::get_owner_node_from_point()
{
    return get_node_from_point(this->getOwner()->getPosition());
}

// get a node from a generic point in 2d space after performing a crap as fuck
// LINEAR SEARCH
//
// TODO: this should be at least a binary search
NodeWeights* GridComponent::get_node_from_point(Vector2 point)
{
  Grid* main_grid     = this->m_owner->getGame()->getWorld()->get_main_grid();
    Vector2 grid_origin = this->m_owner->getGame()->getWorld()->get_top_left();
    Vector2 pos         = {point.x - grid_origin.x, point.y - grid_origin.y};

    int i;
    int index_y;
    int index_x;

    for (i = main_grid->number_of_nodes - 1; i >= 0; --i) {
        if (pos.y >= m_actors_grid[i][0].referring_node->screen_pos.y) {
            index_y = i;
            break;
        }
    }

    for (i = main_grid->number_of_nodes - 1; i >= 0; --i) {
        if (pos.x >= m_actors_grid[0][i].referring_node->screen_pos.x) {
            index_x = i;
            break;
        }
    }

    NodeWeights* result = &(this->m_actors_grid[index_y][index_x]);
    return result;
}
