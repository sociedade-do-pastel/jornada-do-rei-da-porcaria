#include <stdio.h>
#include <unistd.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_RICONS
#include "../include/raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
void launch_game(int difficulty);
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
  // Initialization
  //---------------------------------------------------------------------------------------
  int screenWidth = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "launcher_layout");

  // launcher_layout: controls initialization
  //----------------------------------------------------------------------------------
  bool Button001Pressed = false;
  bool Button002Pressed = false;
  //----------------------------------------------------------------------------------
  /* our banner */
  Texture banner = LoadTexture("assets/banner.png");
  float pos_x = (screenWidth - banner.width) / 2.0f;
  int offset = 90;
  int choice = 0;
  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose() && choice == 0) 
    {
      if (Button001Pressed)
	choice = 1;
      
      if (Button002Pressed)
	choice = 2;
      
      BeginDrawing();
      ClearBackground((Color){240, 255, 244}); 

      // raygui: controls drawing
      //----------------------------------------------------------------------------------
      DrawTextureV(banner, (Vector2){pos_x , 0 }, RAYWHITE);
      GuiGroupBox((Rectangle){ 225, 100 + offset, 325, 205 }, "DIFICULDADE");
      Button001Pressed = GuiButton((Rectangle){ 250, 125 + offset, 275, 50 }, "NORMAL"); 
      Button002Pressed = GuiButton((Rectangle){ 250, 225 + offset, 275, 50 }, "ALTA"); 
      //----------------------------------------------------------------------------------

      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadTexture(banner);
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  if (choice > 0)
    launch_game(choice);
  
  return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
void launch_game (int difficulty)
{
  char arg[40] = {};
#ifdef _WIN32
  sprintf (arg, "jornada_porcaria.exe %d", difficulty);
#else
  sprintf (arg, "./jornada_porcaria %d", difficulty);  
#endif
  system (arg);
}
