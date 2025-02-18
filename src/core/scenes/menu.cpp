
#include "menu.h"
#include "../gui/gui.h"

Menu::Menu() : next(false)  {}

Menu::~Menu() {}

void Menu::draw() {
    int spacing = 10;
    if (GUIButton({10,50,100,35}, "Start", true)) {
        fmt::print("Start button pressed\n");
        this->next = true;
    }
    if (GUIButton({10.0f, 50.0f + 35.0f + static_cast<float>(spacing), 100.0f, 35.0f}, "Options", true)) {
        fmt::print("Options button pressed\n");
    }
    if (GUIButton({10.0f, (50.0f + 35.0f * 2) + (static_cast<float>(spacing) * 2), 100.0f, 35.0f}, "Exit", true)) {
        fmt::print("Exit button pressed\n");
    }
}