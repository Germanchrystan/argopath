#include <raylib.h>
#include <emscripten/emscripten.h>

static void UpdateDrawFrame(void)
{
 BeginDrawing();
 ClearBackground(RAYWHITE);
 DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
 EndDrawing();   
}


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);


    return 0;
}