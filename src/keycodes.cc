#include <iostream>
#include <string>
#include <unordered_map>
#include "keycodes.h"

using std::string;

const std::unordered_map<Keycode, string> keycode_map = []() -> std::unordered_map<Keycode, string> {
    std::unordered_map<Keycode, string> m;
    m[Keycode::H] = "H";
    m[Keycode::J] = "J";
    m[Keycode::K] = "K";
    m[Keycode::L] = "L";
    m[Keycode::W] = "W";
    m[Keycode::ESC] = "ESC";
    m[Keycode::CMD] = "CMD";
    m[Keycode::LEFT] = "LEFT";
    m[Keycode::RIGHT] = "RIGHT";
    m[Keycode::DOWN] = "DOWN";
    m[Keycode::UP] = "UP";
    return m;
}();

std::ostream& operator<<(std::ostream &os, const Keycode &code) {
    if (!keycode_map.contains(code)) return os;
    os << "KEY:" << keycode_map.at(code);
    return os;
}
