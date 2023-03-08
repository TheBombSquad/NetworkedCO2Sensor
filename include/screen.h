#pragma once

#include <LCDKeypad.h>

typedef const void (*ScreenFunction)();

class ActiveScreen {
public:
    LCDKeypad hardware;
    ScreenFunction active_func;
    void set_column(const uint8_t col);
    void print_full_line(const char* const text);
};

namespace NetworkStatScreen {
    const void loop();
}

const static ScreenFunction screens[]{
    NetworkStatScreen::loop,
};

extern ActiveScreen screen;