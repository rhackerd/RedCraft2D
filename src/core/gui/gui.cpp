#include "gui.h"


bool GUIButton(Rectangle bounds, const char* text, bool enabled) {
    if (enabled) {
        bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
        DrawRectangleRounded(bounds, 0.1f, 0.2f, hovered ? DARKGRAY : GRAY);

        int textWidth = MeasureText(text, 20);
        int textHeight = 20;
        int textX = bounds.x + (bounds.width - textWidth) / 2;
        int textY = bounds.y + (bounds.height - textHeight) / 2;

        DrawText(text, textX, textY, 20, WHITE);

        if (hovered) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                return true;
            }
        }
    }

    return false;
}