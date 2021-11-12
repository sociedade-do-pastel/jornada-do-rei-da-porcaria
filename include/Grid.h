#ifndef GRID_H
#define GRID_H
#define NUMBER_OF_NODES_AXIS 16
#define MAP_LIMIT 5
#define NODE_DIAMETER 48

#include <raylib.h>

struct node
{
  unsigned short int count;
  Vector2 screen_pos;
};

struct Grid
{
  /* how many maps have been pushed until now */
  unsigned short int map_count;
  /* the diameter of our node (they're supposed to be squares) */
  unsigned short int node_diameter;

  unsigned short int number_of_nodes;
  
  /* the ``world'' itself */
  unsigned short int types[MAP_LIMIT];
  struct node world[MAP_LIMIT][NUMBER_OF_NODES_AXIS][NUMBER_OF_NODES_AXIS];
};
#endif /* GRID_H */
