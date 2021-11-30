#pragma once
#include <map>
#include <queue>
#include <raylib.h>
#include <string>
#include "Actor.hpp"

// forward declarations
class Game;

class SoundManager : public Actor
{
public:
    // constructor and destructor
    //
    SoundManager(Game* game);
    SoundManager(Game* game, std::string track_name);
    ~SoundManager();

    // actor related
    //
    void updateActor() override;

    // sound specific, sounds are all low duration sounds that can be played,
    // like explosions, for example
    //
    void add_sound(std::string sound_filename);

    // music specific methods
    //
    void pause_music();
    void stop_music();
    void play_music();
    void resume_music();
    void remove_music_track();
    void change_volume(float value);

private:
    std::string track_directory{"assets/"};

    // music related variables
    //
    Music current_track;
    float current_volume{0.1f};
    bool paused{false};

    // sound related variables
    //
    std::queue<Sound> sound_queue;
    std::map<std::string, Sound> loaded_sound_map;

    // audio device control
    bool device_ready{false};
};
