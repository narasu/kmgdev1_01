#include <SFML/Audio.hpp>
#pragma once

class Sound {
public:
    explicit Sound(std::string _file);
    Sound(const Sound& _sound);
    Sound& operator=(const Sound& _sound);
    void play() { snd.play(); }
    void setVolume(float _volume) { snd.setVolume(_volume); }
private:
    std::unique_ptr<sf::SoundBuffer> buffer;
    sf::Sound snd;
};