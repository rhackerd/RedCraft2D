#ifndef ENGINE_H
#define ENGINE_H

#include <fmt/core.h>
#include <raylib.h>

class engine
{
private:
    

public:
    // raylib related functions
    void changeTitle(const char* title);
    void changeWindowSize(int width, int height);
    void changeWindowPosition(int x, int y);
    void setWindowIcon(Image icon);
    void setWindowIcon(const char* filename);
    void setTargetFPS(int fps);
    void setExitKey(int key);
    void initWindow(int width, int height, const char* title);
    bool shouldCloseWindow() { return WindowShouldClose(); }

    // drawing related functions
    void clearBackground(Color color) { ClearBackground(color); }
    void beginDrawing() { BeginDrawing(); }
    void endDrawing() { EndDrawing(); }
    void drawFPS(int x, int y) { DrawFPS(x, y); }



    // class and structure related functions
    void init();
    void deinit();


    engine();
    ~engine();
};


#endif