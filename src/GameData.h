// global game data
#include "hiro/Hiro.h"
#pragma once

using namespace Hiro;

const int VIEWPORT_WIDTH = 320;
const int VIEWPORT_HEIGHT = 180;
const int HUD_HEIGHT = 11;

const std::map<std::string, Hiro::Rect<float>> BOUNDS {
        {"player", Rect<float>(.0f, 2.0f, 6.0f, 8.0f)}, //player
        {"enemy01", Rect<float>(1.0f, 1.0f, 12.0f, 19.0f)}, //crustachnid
        {"enemy02", Rect<float>(1.0f, 6.0f, 12.0f, 23.0f)}, //decaying_mutant
        {"enemy03", Rect<float>(1.0f, 1.0f, 12.0f, 11.0f)} //macrobe
};

const Vector2<float> PLAYER_START { 156.f, 155.f };
const int START_HEALTH = 3;

// score threshold determines when the game increases in difficulty
const std::array<int, 4> SCORE_THRESHOLD { 1000, 4000, 10000, 20000 };

// values to be applied on each stage of game difficulty (array sizes need to be 1 greater than SCORE_THRESHOLD)
const std::array<float, 5> ENEMY_SPAWN_INTERVAL { 2.9f, 2.35f, 1.65f, 1.4f, 1.2f };
const std::array<float, 5> GRASS_SPAWN_INTERVAL { 3.25f, 3.1f, 2.8f, 2.5f, 2.4f };
const std::array<float, 5> STAGE_SPEED { 13.0f, 25.0f, 35.0f, 44.0f, 58.0f };
const std::array<float, 5> ENEMY_FORCE_Y { 25.0f, 45.0f, 60.0f, 85.0f, 105.0f };
const std::array<float, 5> SCORE_PER_ENEMY { 100, 125, 150, 200, 225 };