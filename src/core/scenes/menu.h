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


public:
    Menu();
    ~Menu();
    
    void draw();
    void event();
    void enable();
    void disable();
    bool getNext() { return this->next; }
};

#endif
