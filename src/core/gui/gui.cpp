#include "gui.h"
#include <string.h>
#include <iostream>

Color backgroundColor = GRAY;
Color hoveredColor = DARKGRAY;
Color disabledColor = DARKGRAY;
bool border = true;
Color borderColor = {50, 50, 50, border ? 255 : 0};
float borderRadius = 0.1f;
Color textColor = WHITE;



bool GUI::DrawButton(Rectangle bounds, const char* text, bool enabled, Font customFont) {
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), bounds);
    Color buttonColor = enabled ? backgroundColor : disabledColor;
    if (enabled && isHovered) buttonColor = hoveredColor;
    DrawRectangleRounded(bounds, borderRadius-0.05f, 0.2f, buttonColor);
    DrawRectangleRoundedLinesEx(bounds, borderRadius, 0.2f, 2.0f, borderColor);

    int textWidth = MeasureText(text, 20);
    int textHeight = 20;
    int textX = bounds.x + (bounds.width - textWidth) / 2;
    int textY = bounds.y + (bounds.height - textHeight) / 2;


    DrawTextEx(customFont, text, {(float)textX, (float)textY}, 20, 1.0f, textColor);

    if (isHovered && enabled) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return true;
        }
    }

    return false;
}

bool GUI::DrawInput(Rectangle bounds, char* text, int maxLength, bool enabled, Font customFont) {
    static bool active = false; // Zda je input aktivní
    static int cursorIndex = 0; // Track the position in the text
    int textSize = MeasureText(text, 20);
    float maxsize = (float)(MeasureText("F", 20) * maxLength + (2 * 5));
    if (textSize > maxsize) maxsize = textSize + (2 * 5);
    Rectangle editedBounds = {(float)bounds.x, (float)bounds.y, maxsize, (float)bounds.height};

    if (enabled && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), editedBounds)) {
        active = true;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        active = false;
    }

    DrawRectangleRounded(editedBounds, 0.0f, 0.2f, active ? disabledColor : enabled ? backgroundColor : disabledColor);
    DrawRectangleRoundedLinesEx(editedBounds, borderRadius, .2f, 2.0f, borderColor);

    if (active && enabled) {
        int key = GetCharPressed();
        while (key > 0) {
            if (cursorIndex < maxLength) {
                text[cursorIndex] = (char)key;
                cursorIndex++;
                text[cursorIndex] = '\0'; // Null-terminate the string
            }
            key = GetCharPressed();
        }

        // Backspace handling
        if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && cursorIndex > 0) {
            cursorIndex--;
            text[cursorIndex] = '\0'; // Null-terminate the string
        }
    }

    DrawTextEx(customFont, text, {bounds.x + 5, bounds.y + (bounds.height - 20) / 2}, 20, 1.0f, textColor);

    return active;
}
