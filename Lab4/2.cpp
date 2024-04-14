#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <map>
using namespace std;
int main() {
    const char *keyboard = "/dev/input/event3";
    int fd = open(keyboard, O_RDONLY);
    //cout<<fd<<endl;
    if (fd == -1) {
        cerr << "Error while opening\n";
        return 1;
    }
map<int, string> key_map = {
    {KEY_A, "a"}, {KEY_B, "b"}, {KEY_C, "c"}, {KEY_D, "d"}, {KEY_E, "e"}, {KEY_F, "f"}, {KEY_G, "g"}, {KEY_H, "h"},
    {KEY_I, "i"}, {KEY_J, "j"}, {KEY_K, "k"}, {KEY_L, "l"}, {KEY_M, "m"}, {KEY_N, "n"}, {KEY_O, "o"}, {KEY_P, "p"},
    {KEY_Q, "q"}, {KEY_R, "r"}, {KEY_S, "s"}, {KEY_T, "t"}, {KEY_U, "u"}, {KEY_V, "v"}, {KEY_W, "w"}, {KEY_X, "x"},
    {KEY_Y, "y"}, {KEY_Z, "z"}, {KEY_SPACE, "SPACE"}, {KEY_ENTER, "ENTER"}, {KEY_BACKSPACE, "BACKSPACE"}, {KEY_TAB, "TAB"},
    {KEY_ESC, "ESCAPE"},
    {KEY_0, "0"}, {KEY_1, "1"}, {KEY_2, "2"}, {KEY_3, "3"}, {KEY_4, "4"}, {KEY_5, "5"}, {KEY_6, "6"}, {KEY_7, "7"},
    {KEY_8, "8"}, {KEY_9, "9"}, {KEY_MINUS, "-"}, {KEY_EQUAL, "="}, {KEY_LEFTBRACE, "["}, {KEY_RIGHTBRACE, "]"},
    {KEY_SEMICOLON, ";"}, {KEY_APOSTROPHE, "'"}, {KEY_GRAVE, "`"}, {KEY_BACKSLASH, "\\"}, {KEY_COMMA, ","},
    {KEY_DOT, "."}, {KEY_SLASH, "/"},
    {KEY_F1, "F1"}, {KEY_F2, "F2"}, {KEY_F3, "F3"}, {KEY_F4, "F4"}, {KEY_F5, "F5"},
    {KEY_F6, "F6"}, {KEY_F7, "F7"}, {KEY_F8, "F8"}, {KEY_F9, "F9"}, {KEY_F10, "F10"},
    {KEY_F11, "F11"}, {KEY_F12, "F12"},
    {KEY_LEFTSHIFT, "LEFTSHIFT"}, {KEY_RIGHTSHIFT, "RIGHTSHIFT"}, {KEY_LEFTCTRL, "LEFTCTRL"}, {KEY_RIGHTCTRL, "RIGHTCTRL"},
    {KEY_LEFTALT, "LEFTALT"}, {KEY_RIGHTALT, "RIGHTALT"}, {KEY_LEFTMETA, "LEFTMETA"}, {KEY_RIGHTMETA, "RIGHTMETA"},
    {KEY_CAPSLOCK, "CAPSLOCK"}, {KEY_NUMLOCK, "NUMLOCK"}, {KEY_SCROLLLOCK, "SCROLLLOCK"},
    {KEY_PRINT, "PRINT"}, {KEY_PAUSE, "PAUSE"}, {KEY_INSERT, "INSERT"}, {KEY_HOME, "HOME"},
    {KEY_END, "END"}, {KEY_PAGEUP, "PAGEUP"}, {KEY_PAGEDOWN, "PAGEDOWN"},
    {KEY_LEFT, "LEFT"}, {KEY_RIGHT, "RIGHT"}, {KEY_UP, "UP"}, {KEY_DOWN, "DOWN"},
    {KEY_DELETE, "DELETE"}
};
    struct input_event ev;
    while (true) {
        read(fd, &ev, sizeof(struct input_event));
        if (ev.type == EV_KEY && ev.value == 1) {
            //cout << "Key " << ev.code << " is pressed\n";
             if (key_map.find(ev.code) != key_map.end()) {
                cout << "Key " << key_map[ev.code] << " is pressed\n";
            }
        }
    }
    close(fd);
}
