#ifndef KEYCODES_H
#define KEYCODES_H

#include <iostream>
#include "utils.h"

enum Keycode {
    H = 4,
    J = 38,
    K = 40,
    L = 37,
    W = 13,
    ESC = 53,
    CMD = 55,
    LEFT = 123,
    RIGHT = 124,
    DOWN = 125,
    UP = 126,
    EMPTY = MAX_INT
};

std::ostream& operator<<(std::ostream &os, const Keycode &code);

#endif /* KEYCODES_H */
