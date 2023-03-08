#include <screen.h>

void ActiveScreen::set_column(const uint8_t col) {
    this->hardware.setCursor(0, col);
}

void ActiveScreen::print_full_line(const char* const text) {
    char buffer[17];
    memset(buffer, ' ', 16);
    buffer[16] = '\0';
    memcpy(buffer, text, strlen(text));
    this->hardware.print(buffer);
}