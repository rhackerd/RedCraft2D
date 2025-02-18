
#include "menu.h"
#include "../gui/gui.h"
#include "../utils/logging.hpp"

Menu::Menu() : next(false) {
    strcpy(this->text, "");
}

Menu::~Menu() {}

void Menu::draw() {
    int spacing = 10;
    if (GUI::DrawButton({10,50,100,35}, "Start", true)) {
        info("Start button pressed");
        this->next = true;
    }
    if (GUI::DrawButton({10.0f, 50.0f + 35.0f + static_cast<float>(spacing), 100.0f, 35.0f}, "Options", true)) {
        info("Options button pressed");
    }
    if (GUI::DrawButton({10.0f, (50.0f + 35.0f * 2) + (static_cast<float>(spacing) * 2), 100.0f, 35.0f}, "Exit", true)) {
        info("Exit button pressed");
    }

    
    GUI::DrawInput({10.0f, 200.0f, 100.0f, 35.0f}, text, 21, true);


}