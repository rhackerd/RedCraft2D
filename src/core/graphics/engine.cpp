#include "engine.h"

engine::engine() {}

engine::~engine() {}

void engine::init() {
    fmt::print("Engine initialized\n");
}

void engine::deinit() {
    fmt::print("Engine deinitialized\n");
}

void engine::initWindow(int width, int height, const char* title) {
    InitWindow(width, height, title);
}

void engine::changeTitle(const char* title) {
    SetWindowTitle(title);
}

void engine::changeWindowSize(int width, int height) {
    SetWindowSize(width, height);
}

void engine::changeWindowPosition(int x, int y) {
    SetWindowPosition(x, y);
}

void engine::setWindowIcon(Image icon) {
    SetWindowIcon(icon);
}

void engine::setWindowIcon(const char* filename) {
    Image icon = LoadImage(filename);
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void engine::setTargetFPS(int fps) {
    setTargetFPS(fps);
}

void engine::setExitKey(int key) {
    SetExitKey(key);
}
