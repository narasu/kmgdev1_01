// global game data
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

const Vector2<float> PLAYER_START { 160.f, 155.f };
const int HEALTH = 3;

const int SCORE_THRESHOLD[3] { 1000, 2000, 4000 };
const float SPAWN_INTERVAL[4] { 3.0f, 2.0f, 1.0f, 0.5f };
const float ENEMY_SPEED[4] { 15.0f, 20.0f, 25.0f, 30.0f };

const std::string START_TEXT = "PRESS LEFT OR RIGHT ARROW KEYS TO MOVE";
const std::string END_TEXT = "YOU DIED \n PRESS ANY KEY TO RESTART";