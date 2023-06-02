#include "hiro/Hiro.h"
#pragma once

using namespace Hiro;

const int VIEWPORT_WIDTH = 320;
const int VIEWPORT_HEIGHT = 180;

const std::map<std::string, Hiro::Rect<float>> BOUNDS {
        {"player", Rect<float>(.0f, 2.0f, 6.0f, 8.0f)}, //player
        {"enemy01", Rect<float>(1.0f, 1.0f, 12.0f, 19.0f)}, //crustachnid
        {"enemy02", Rect<float>(1.0f, 6.0f, 12.0f, 23.0f)}, //decaying_mutant
        {"enemy03", Rect<float>(1.0f, 1.0f, 12.0f, 11.0f)} //macrobe
};

