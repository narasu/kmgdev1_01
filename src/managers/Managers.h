//forward declaration of managers
#ifndef KMGDEV1_01_MANAGERS_H
#define KMGDEV1_01_MANAGERS_H

#include <SFML/Graphics.hpp>
#include <memory>
#pragma once

class TextureManager;
class EntityManager;
class GameManager;
class InterfaceManager;
class AudioManager;
class Spawner; // had to declare this here because it wouldn't link properly otherwise

#include "TextureManager.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "InterfaceManager.h"
#include "AudioManager.h"
#include "../spawner/Spawner.h"

#endif //KMGDEV1_01_MANAGERS_H
