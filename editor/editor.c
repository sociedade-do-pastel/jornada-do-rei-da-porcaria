/*******************************************************************************************
 *
 *   Mapitor v0.5 - Simple map editor
 *
 *   Map editor for the game ``Jornada do rei da porcaria''. A quarter or so of
 *   this code was generated by Ray's ``rguilayout'' program;
 *
 **********************************************************************************************/
/* C libraries */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* raylib stuff */
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_RICONS

#include "../include/raygui.h"
#include "../include/Grid.h"
#include "../include/MapConstants.h"

//----------------------------------------------------------------------------------
// Standard functions declarations
//----------------------------------------------------------------------------------
/* load and unload our assets into the screen */
Texture** load_textures ();
bool unload_textures (Texture** texture_array);

/* initialize (clean) our map, draw and save it */
void clear_map (struct Grid* map);
void draw_map (struct Grid* map, Texture** texture_array,
	       const int first_x, const int first_y);
void save_map (struct Grid* map);
void shift_map (struct Grid* map);

/* miscellaneous */
struct node* get_node_from_point (struct Grid* map, const Vector2 point);
void check_button (int button, int new_value, struct Grid* map);
void check_mouse_wheel (int* texture_index);
Vector2 translate_to_origin (Vector2 original_point, Vector2 offset);
void draw_current_selected_texture(Texture* texture_array, Vector2 position,
                                   int current_texture, int width);
//------------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------------
/* where on the window our grid should be drawn  */
const int grid_first_x = 250;
const int grid_first_y = 195;
const char* asset_folder = "../assets/";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
  // Initialization
  //---------------------------------------------------------------------------------------
  int screenWidth = 1280;
  int screenHeight = 1024;
  struct Grid map = {0};
  int texture_index = 0;
  InitWindow(screenWidth, screenHeight, "mapitor");
  /* loading our textures and map */
  Texture** ground_textures = load_textures (ground_textures);
  map.number_of_nodes = NUMBER_OF_NODES_AXIS;
  map.node_diameter = NODE_DIAMETER;
  map.map_count = 0;
  clear_map (&map);

  // mapitor: controls initialization
  //----------------------------------------------------------------------------------
  int ListView000ScrollIndex = 0;
  int ListView000Active = 0;
  int ScrollBarIndex = 0;
  bool TextBox002EditMode = false;
  bool Button001Pressed = false;
  bool Button002Pressed = false;
  bool Button003Pressed = false;
  //----------------------------------------------------------------------------------

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      //----------------------------------------------------------------------------------
      check_mouse_wheel (&texture_index);
      check_button (MOUSE_BUTTON_LEFT, texture_index,  &map);
      check_button (MOUSE_BUTTON_RIGHT, 1, &map);

      /* this ListView can assume three indexes (0, 1, 2), those will represent
	 our terrain types */
      if (ListView000Active >= 0)
	map.types[map.map_count] = ListView000Active;

      if (Button001Pressed)
	clear_map (&map);

      if (Button002Pressed)
	shift_map (&map);
      
      if (Button003Pressed)
	save_map (&map);

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

      ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

      // raygui: controls drawing
      //----------------------------------------------------------------------------------
      ListView000Active = GuiListView((Rectangle){ 50, 225, 150, 100 },
				      "FLORESTA;DESERTO;NEVE",
				      &ListView000ScrollIndex,
				      ListView000Active);
      
      GuiGroupBox((Rectangle){ 50, 215, 150, 110 }, "TIPO DE TERRENO");
      Button001Pressed = GuiButton((Rectangle){ 50, 350, 150, 25 }, "CLEAR");
      Button002Pressed = GuiButton((Rectangle){ 50, 400, 150, 25 }, "PUSH");
      Button003Pressed = GuiButton((Rectangle){ 50, 450, 150, 25 }, "SALVAR"); 
      GuiGroupBox((Rectangle){ 50, 390, 150, 85 }, "EXPORTAR");
      GuiLabel((Rectangle){ 250, 150, 125, 25 }, "MAPA");
      GuiProgressBar ((Rectangle){ 500, 150, 125, 25 },
		      "1  ",
		      " limite",
		      map.map_count,
		      0,
		      MAP_LIMIT - 1);
      
      GuiLabel((Rectangle){ 50, 475, 150, 25 }, "INSTRUCOES:");
      GuiLabel((Rectangle){ 50, 500, 150, 25 }, "RODINHA: MUDAR TILE");
      GuiLabel((Rectangle){ 50, 525, 150, 25 }, "MOUSE 1: APLICAR TILE");
      GuiLabel((Rectangle){ 50, 550, 150, 25 }, "MOUSE 2: APAGAR TILE");
      GuiLabel((Rectangle){ 50, 600, 150, 25 }, "TILE ATUAL:");
      
      //----------------------------------------------------------------------------------

      // then draw our map
      draw_map (&map, ground_textures, grid_first_x, grid_first_y);
      // and the current selected texture
      draw_current_selected_texture (ground_textures[map.types[map.map_count]],
				     (Vector2){50, 630},
				     texture_index,
				     map.node_diameter);
      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  unload_textures (ground_textures);
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

//------------------------------------------------------------------------------------
// Standard Functions Definitions
//------------------------------------------------------------------------------------
Texture**
load_textures ()
{
  Texture** texture_array;
  texture_array = malloc (sizeof (Texture*) * NUMBER_OF_MAP_TYPES);

  int i;
  for (i = 0; i < NUMBER_OF_MAP_TYPES; ++i)
    texture_array[i] = malloc (sizeof (Texture) * NUMBER_OF_GRD_TEXTURES);

  /* now we load them properly */
  char temp[50] = {0};
  int j;
  for (i = 0; i < NUMBER_OF_MAP_TYPES; ++i)
    {
      strcpy (temp, texture_names[i]);
      for (j = 0; j < NUMBER_OF_GRD_TEXTURES; ++j)
	{
	  char filename[50] = {0};
	  sprintf(filename, temp, asset_folder, j);
	  texture_array[i][j] = LoadTexture (filename);
	}
    }
  
  return texture_array;
}

bool
unload_textures (Texture** texture_array)
{
  int i;
  int j;
    
  for (i = 0; i < NUMBER_OF_MAP_TYPES; ++i)
    for (j = 0; j < NUMBER_OF_GRD_TEXTURES; ++j)
      UnloadTexture(texture_array[i][j]);

  for (i = 0; i < NUMBER_OF_MAP_TYPES; i++)
    free (texture_array[i]);
  
  free (texture_array);
  return true;
}

void
clear_map (struct Grid* map)
{
  int i;
  int j;
  for (i = 0; i < map->number_of_nodes; ++i)
    {
      for (j = 0; j < map->number_of_nodes; ++j)
	{
	  if (i == 0
	      || j == 0
	      || i == map->number_of_nodes - 1
	      || j == map->number_of_nodes - 1)
	    map->world[map->map_count][i][j].count = 0;
	  else
	    map->world[map->map_count][i][j].count = 1;
	}
    }
      
}

void
draw_map (struct Grid* map, Texture** texture_array,
	  const int first_x, const int first_y)
{
  int i;
  int j;
  int pos_x;
  int pos_y;
  
  for (i = 0; i < map->number_of_nodes; ++i)
    {
      pos_y = first_y + (i * map->node_diameter);
  
      for (j = 0, pos_x = first_x ; j < map->number_of_nodes; ++j)
        {
          pos_x = first_x + (j * map->node_diameter);

	  
          DrawTextureRec(texture_array[map->types[map->map_count]]
			 [map->world[map->map_count][i][j].count],
                         (Rectangle){0.0f, 0.0f, texture_array[0][1].width,
                                     texture_array[0][1].width},
                         (Vector2){pos_x, pos_y}, WHITE);

          map->world[map->map_count][i][j].screen_pos
	    = translate_to_origin((Vector2){pos_x, pos_y},
				  (Vector2){first_x, first_y});
        }
    }
}

struct node*
get_node_from_point (struct Grid* map, const Vector2 point)
{
  if ((point.x < map->world[map->map_count][0][0].screen_pos.x ||
       point.x > map->world[map->map_count][0][map->number_of_nodes - 1]
       .screen_pos.x +
       map->node_diameter ||
       (point.y < map->world[map->map_count][0][0].screen_pos.y ||
        point.y > map->world[map->map_count][map->number_of_nodes - 1][0]
	.screen_pos.y +
	map->node_diameter)))
    return NULL;

  /* shitty linear search */
  int i;
  int index_y;
  int index_x;
  
  for (i = map->number_of_nodes - 1 ; i >= 0 ; --i)
    {
      if (point.y >=  map->world[map->map_count][i][0].screen_pos.y)
	{
	  index_y = i;
	  break;
	}
    }

  for (i = map->number_of_nodes - 1 ; i >= 0 ; --i)
    {
      if (point.x >=  map->world[map->map_count][0][i].screen_pos.x)
	{
	  index_x = i;
	  break;
	}
    }
  
  return &(map->world[map->map_count][index_y][index_x]);
}

void
check_button (int button, int new_value, struct Grid* map)
{
  if (IsMouseButtonPressed (button))
    {
      Vector2 p_dash = translate_to_origin ((Vector2) {GetMouseX (), GetMouseY ()},
					    (Vector2) {grid_first_x, grid_first_y});
      
      struct node* temp_node = get_node_from_point (map, p_dash);

      if (!temp_node)
	return ;
      
      unsigned short int* value = &(temp_node->count);
      *value = new_value;

    }
}

void
save_map (struct Grid* map)
{
  SaveFileData ("map.jooj", map, sizeof (struct Grid));
}

void
shift_map (struct Grid* map)
{
  if (!(map->map_count > MAP_LIMIT - 2))
    {
      map->map_count += 1;
      clear_map (map);
    }
}

Vector2
translate_to_origin (Vector2 from, Vector2 to)
{
  return (Vector2){from.x - to.x, from.y -  to.y};
}

void check_mouse_wheel (int* index)
{
  float wheel_direction = GetMouseWheelMove ();
  int increase_value = 0;
  int texture_index = *index;
    
  if (wheel_direction > 0)
    increase_value = 1;
  else if (wheel_direction < 0)
    increase_value = -1;

  if (texture_index + increase_value >= NUMBER_OF_GRD_TEXTURES)
    texture_index = 0;
  else if (texture_index + increase_value < 0)
    texture_index = NUMBER_OF_GRD_TEXTURES - 1;
  else
    texture_index += increase_value;

  *index = texture_index;
}

void draw_current_selected_texture (Texture* texture_array,
				    Vector2 position,
				    int current_texture,
				    int width)
{
  DrawTextureRec (texture_array[current_texture],
		  (Rectangle){0.0f, 0.0f, width, width},
		  position,
		  WHITE);
}
