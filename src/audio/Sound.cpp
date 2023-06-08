//
// Created by Yamada on 7-6-2023.
//

#include <iostream>
#include "Sound.h"

Sound::Sound(std::string _file) {
    buffer = std::make_unique<sf::SoundBuffer>();

    if (!buffer->loadFromFile(_file)) {
        std::cout << "Can't load file " + _file << std::endl;
    }
    snd.setBuffer(*buffer);
}

Sound::Sound(const Sound &_sound) {
    if (this == &_sound) {
        return;
    }
    buffer = std::make_unique<sf::SoundBuffer>(*_sound.buffer);
    snd = _sound.snd;
}

Sound &Sound::operator=(const Sound &_sound) {
    if (this == &_sound) {
        return *this;
    }
    buffer = std::make_unique<sf::SoundBuffer>(*_sound.buffer);
    snd = _sound.snd;
    return *this;
}

