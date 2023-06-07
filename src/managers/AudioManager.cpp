#include "Managers.h"

AudioManager::AudioManager() {
    music = std::make_unique<sf::Music>();
    if (!music->openFromFile("assets/audio/bgm.ogg")) {
        std::cout << "Can't open music file!" << std::endl;
    }
    music->setLoop(true);
    music->setVolume(MUSIC_VOLUME);
    sounds[PlayerHitSound] = std::make_unique<Sound>("assets/audio/hit.ogg");
    sounds[PlayerHitSound]->setVolume(SFX_VOLUME);
    sounds[EnemySpawnSound] = std::make_unique<Sound>("assets/audio/enemy_spawn.ogg");
    sounds[EnemySpawnSound]->setVolume(SFX_VOLUME);
    sounds[LoseSound] = std::make_unique<Sound>("assets/audio/lose.ogg");
    sounds[LoseSound]->setVolume(MUSIC_VOLUME);
}

AudioManager &AudioManager::operator=(const AudioManager &_audioManager) {
    if (this == &_audioManager) {
        return *this;
    }
    copy(_audioManager);
    return *this;
}

AudioManager::AudioManager(const AudioManager &_audioManager) {
    if (this == &_audioManager) {
        return;
    }
    copy(_audioManager);
}

void AudioManager::copy(const AudioManager &_audioManager) {
    // sf::Music doesn't allow copying, so a new instance needs to be constructed
    music = std::make_unique<sf::Music>();
    if (!music->openFromFile(_audioManager.musicFile)) {
        std::cout << "Can't open music file!" << std::endl;
    }
    musicFile = _audioManager.musicFile;
    music->setLoop(_audioManager.music->getLoop());

    for (auto &it : _audioManager.sounds) {
        sounds[it.first] = std::make_unique<Sound>(*it.second);
    }
}

void AudioManager::playSound(SoundType _soundType) {
    auto it = sounds.find(_soundType);
    if (it != sounds.end() && it->second != nullptr) {
        sounds[_soundType]->play();
    }
}
