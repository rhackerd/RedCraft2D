#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <fmt/core.h>

// Remove this definition from the header
// #define RAYGUI_IMPLEMENTATION

class Menu
{
private:
    bool next;
    char text[21];
    Font customFont;


public:
    Menu();
    ~Menu();

    const char* getPlayerName();    
    void draw();
    void event();
    void enable();
    void disable();
    bool getNext() { return this->next; }
};

#endif
