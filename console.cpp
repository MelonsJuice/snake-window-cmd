#include "console.h"

COORD getpos() {
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (GetConsoleScreenBufferInfo(hCon, &info)) {
        return info.dwCursorPosition;
    } else {
        return COORD{ 0, 0 };
    }
}

void moveto(short x, short y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y });
}

void setcolor(int fg, int bg /*= BLACK*/) {
    int color = bg * 16 + fg;
    SetConsoleTextAttribute(hCon, color);
}

void setcursor(bool visible) {
    CONSOLE_CURSOR_INFO cursor_info;

    cursor_info.bVisible = visible;
    cursor_info.dwSize = 1;

    SetConsoleCursorInfo(hCon, &cursor_info);
}