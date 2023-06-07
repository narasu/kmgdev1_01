// global game data
#include "hiro/Hiro.h"
#pragma once

using namespace Hiro;

const int VIEWPORT_WIDTH = 135;
const int VIEWPORT_HEIGHT = 240;
const int HUD_HEIGHT = 11;

const float MUSIC_VOLUME = 25.0f;
const float SFX_VOLUME = 30.0f;

const std::map<std::string, Hiro::Rect<float>> BOUNDS {
        {"player", Rect<float>(.0f, 2.0f, 6.0f, 8.0f)},
        {"enemy01", Rect<float>(1.0f, 1.0f, 12.0f, 19.0f)}, //crustachnid
        {"enemy02", Rect<float>(1.0f, 6.0f, 12.0f, 23.0f)}, //decaying_mutant
        {"enemy03", Rect<float>(1.0f, 1.0f, 12.0f, 11.0f)} //macrobe
};

const Vector2<float> PLAYER_START { 63.5f, 215.f };
const float PLAYER_SPEED = 65.0f;
const int START_HEALTH = 3;

// score threshold determines when the game increases in difficulty
const std::array<int, 4> SCORE_THRESHOLD { 1000, 5000, 10000, 25000 };

// values to be applied on each stage of game difficulty (array sizes need to be 1 greater than SCORE_THRESHOLD)
const std::array<float, 5> ENEMY_SPAWN_INTERVAL { 1.9f, 1.65f, 1.15f, .95f, .8f };
const std::array<float, 5> GRASS_SPAWN_INTERVAL { 3.25f, 2.9f, 2.4f, 2.1f, 1.8f };
const std::array<float, 5> STAGE_SPEED { 15.0f, 30.0f, 60.0f, 90.0f, 120.0f };
const std::array<float, 5> ENEMY_FORCE_Y { 28.0f, 65.0f, 90.0f, 125.0f, 185.0f };
const std::array<float, 5> SCORE_PER_ENEMY { 100, 125, 150, 200, 225 };