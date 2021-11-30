#include "../include/SoundManager.hpp"
#include <raylib.h>

SoundManager::SoundManager(Game* game, std::string track_name)
    : SoundManager{game}
{
    this->current_track
        = LoadMusicStream((this->track_directory + track_name).c_str());

    if (this->device_ready) {
        SetMusicVolume(current_track, current_volume);
        play_music();
    }
}

SoundManager::SoundManager(Game* game) : Actor{game}
{
    InitAudioDevice();
    this->current_track = Music{};

    if (IsAudioDeviceReady())
        this->device_ready = true;
}

SoundManager::~SoundManager()
{
    remove_music_track();

    while (!(this->sound_queue.empty())) {
        UnloadSound(this->sound_queue.front());
        this->sound_queue.pop();
    }

    CloseAudioDevice();
}

void SoundManager::updateActor()
{
    if (!(this->device_ready))
        return;
    
    UpdateMusicStream(this->current_track);

    if (!(sound_queue.empty())) {
        Sound& current_sound{this->sound_queue.front()};
        PlaySound(current_sound);
        sound_queue.pop();
    }
}

void SoundManager::resume_music()
{
    if (!IsMusicStreamPlaying(this->current_track)) {
        ResumeMusicStream(this->current_track);
        this->paused = false;
    }
}

void SoundManager::change_volume(float value)
{
    if ((this->current_volume + value) >= 1.0f
        || (this->current_volume + value) < 0.0f)
        return;

    this->current_volume += value;

    SetMusicVolume(this->current_track, this->current_volume);
}

void SoundManager::pause_music()
{
    if (IsMusicStreamPlaying(this->current_track)) {
        PauseMusicStream(this->current_track);
        this->paused = true;
    }
}

void SoundManager::stop_music()
{
    StopMusicStream(this->current_track);
}

void SoundManager::play_music()
{
    if (!IsMusicStreamPlaying(this->current_track))
        PlayMusicStream(this->current_track);
}

void SoundManager::remove_music_track()
{
    this->stop_music();
    UnloadMusicStream(this->current_track);
    current_track = Music{};
}

void SoundManager::add_sound(std::string sound_filename)
{
    Sound sound_to_add;

    if (loaded_sound_map.find(sound_filename) == loaded_sound_map.end()) {
        sound_to_add
            = LoadSound((this->track_directory + sound_filename).c_str());

        loaded_sound_map.insert(std::make_pair(sound_filename, sound_to_add));
    }
    else {
        sound_to_add = loaded_sound_map.at(sound_filename);
    }

    this->sound_queue.push(sound_to_add);
}
