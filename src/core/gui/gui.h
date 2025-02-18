#ifndef GUI_H
#define GUI_H
#include <raylib.h>


namespace GUI {
    bool DrawButton(Rectangle bounds, const char* text, bool enabled);
    bool DrawInput(Rectangle bounds, char* text, int maxLenght, bool enabled);
}


#endif