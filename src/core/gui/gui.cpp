#include "gui.h"
#include <string.h>
#include <iostream>

bool GUI::DrawButton(Rectangle bounds, const char* text, bool enabled, Font customFont, const GUI::Style& style) {
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), bounds);
    Color buttonColor = enabled ? style.backgroundColor : style.disabledColor;
    if (enabled && isHovered) buttonColor = style.hoveredColor;

    DrawRectangleRounded(bounds, style.borderRadius, 6, buttonColor);
    DrawRectangleRoundedLinesEx(bounds, style.borderRadius, 6, 2.0f, style.borderColor);

    int textWidth = MeasureTextEx(customFont, text, style.fontSize, 1.0f).x;
    int textHeight = style.fontSize;
    int textX = bounds.x + (bounds.width - textWidth) / 2;
    int textY = bounds.y + (bounds.height - textHeight) / 2;

    DrawTextEx(customFont, text, {(float)textX, (float)textY}, style.fontSize, 1.0f, style.textColor);

    return isHovered && enabled && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool GUI::DrawButton(Rectangle bounds, const char* text, bool enabled, Font customFont) {
    Style style;
    return DrawButton(bounds, text, enabled, customFont, style);
}

bool GUI::DrawInput(Rectangle bounds, char* text, int maxLength, bool enabled, Font customFont, const GUI::Style& style) {
    static bool active = false;
    static int cursorIndex = 0;

    int textSize = MeasureText(text, style.fontSize);
    float maxsize = (float)(MeasureText("F", style.fontSize) * maxLength + (2 * 5));
    if (textSize > maxsize) maxsize = textSize + (2 * 5);
    
    Rectangle editedBounds = {bounds.x, bounds.y, maxsize, bounds.height};

    if (enabled && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), editedBounds)) {
        active = true;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        active = false;
    }

    DrawRectangleRounded(editedBounds, style.borderRadius, 6, active ? style.disabledColor : enabled ? style.backgroundColor : style.disabledColor);
    DrawRectangleRoundedLinesEx(editedBounds, style.borderRadius, 6, 2.0f, style.borderColor);

    if (active && enabled) {
        int key = GetCharPressed();
        while (key > 0) {
            if (cursorIndex < maxLength) {
                text[cursorIndex] = (char)key;
                cursorIndex++;
                text[cursorIndex] = '\0';
            }
            key = GetCharPressed();
        }

        if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && cursorIndex > 0) {
            cursorIndex--;
            text[cursorIndex] = '\0';
        }
    }

    DrawTextEx(customFont, text, {bounds.x + 5, bounds.y + (bounds.height - style.fontSize) / 2}, style.fontSize, 1.0f, style.textColor);

    return active;
}

bool GUI::DrawInput(Rectangle bounds, char* text, int maxLength, bool enabled, Font customFont) {
    Style style;
    return DrawInput(bounds, text, maxLength, enabled, customFont, style);
}


void GUI::DrawText(const char* text, int x, int y, int fontSize, Color color, Font customFont, const GUI::Style& style) {
    DrawTextEx(customFont, text, {(float)x, (float)y}, style.fontSize, style.fontSpacing, style.textColor);
}

void GUI::DrawText(const char* text, int x, int y, int fontSize, Color color, Font customFont) {
    Style style;
    DrawText(text, x, y, fontSize, color, customFont, style);
}