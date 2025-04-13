
#include "menu.h"
#include "../gui/gui.h"
#include "../utils/logging.hpp"

// NOTE: does the job so i dont core for the time being
// TODO: Rewrite later

Menu::Menu() : next(false), customFont() {
    strcpy(this->text, "");
}

Menu::~Menu() {
    UnloadFont(customFont);
}

void Menu::draw() {
    if (this->customFont.baseSize == 0) {
        customFont = LoadFont("bin/Debug/assets/fonts/font.ttf");
        SetTextureFilter(customFont.texture, TEXTURE_FILTER_TRILINEAR);
        info("Loaded custom font");
    }


    int spacing = 10;
    if (GUI::DrawButton({10,50,100,35}, "Start", true, customFont)) {
        info("Start button pressed");
        this->next = true;
    }
    if (GUI::DrawButton({10.0f, 50.0f + 35.0f + static_cast<float>(spacing), 100.0f, 35.0f}, "Options", true, customFont)) {
        info("Options button pressed");
    }
    if (GUI::DrawButton({10.0f, (50.0f + 35.0f * 2) + (static_cast<float>(spacing) * 2), 100.0f, 35.0f}, "Exit", true, customFont)) {
        info("Exit button pressed");
    }


    GUI::DrawInput({10.0f, 200.0f, 100.0f, 35.0f}, text, 21, true, customFont);
    std::string Thetext = fmt::format("Your name would be {}", text);
    DrawTextEx(customFont, Thetext.c_str(), {10.0f, 250.0f}, 32, 1.0f, BLACK);
    DrawTextEx(customFont, Thetext.c_str(), {10.0f, 300.0f}, 20, 1.0f, BLACK);


}

const char* Menu::getPlayerName() {return text;};