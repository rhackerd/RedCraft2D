#ifndef GUI_H
#define GUI_H

#include <raylib.h>

namespace GUI {
    struct Style {
        // Background colors
        Color backgroundColor = GRAY;
        Color hoveredColor = DARKGRAY;
        Color disabledColor = DARKGRAY;

        // Border properties
        bool border = true;
        Color borderColor = {50, 50, 50, 255}; // Set dynamically in constructor
        float borderRadius = 0.1f;

        // Text properties
        Color textColor = WHITE;
        int fontSize = 25;
        Color hoveredColorText = WHITE;
        Color disabledColorText = DARKGRAY;
        float fontSpacing = 1.0f;

        // Constructor to adjust `borderColor` alpha based on `border`
        Style() {
            borderColor.a = border ? 255 : 0;
        }
    };
    // more complex functions
    bool DrawButton(Rectangle bounds, const char* text, bool enabled, Font customFont); 
    bool DrawButton(Rectangle bounds, const char* text, bool enabled, Font customFont, const Style& style); 
    bool DrawInput(Rectangle bounds, char* text, int maxLength, bool enabled, Font customFont); 
    bool DrawInput(Rectangle bounds, char* text, int maxLength, bool enabled, Font customFont, const Style& style);


    // simple functions
    void DrawText(const char* text, int x, int y, int fontSize, Color color, Font customFont, const Style& style);
    void DrawText(const char* text, int x, int y, int fontSize, Color color, Font customFont);
};

#endif