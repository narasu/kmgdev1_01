#include "Managers.h"
#include <SFML/Audio.hpp>
#include "../enums/SoundType.h"
#include "../audio/Sound.h"
#pragma once
class AudioManager {
public:
    AudioManager();
    AudioManager(const AudioManager &_audioManager);
    AudioManager& operator=(const AudioManager &_audioManager);
    void playMusic() { music->play(); }
    void stopMusic() { music->stop(); }
    void increaseMusicPitch(float _pitch) { music->setPitch(music->getPitch() + _pitch);}
    void resetMusicPitch() { music->setPitch(1.0f); }
    void playSound(SoundType _soundType);
private:
    void copy(const AudioManager &_audioManager);
    std::unique_ptr<sf::Music> music;
    std::map<SoundType, std::unique_ptr<Sound>> sounds;
    std::string musicFile = "assets/audio/bgm.ogg";

};

