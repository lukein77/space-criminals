#include "Audio.h"

/* Audio constructor */
Audio::Audio() {}

/* Audio destructor */
Audio::~Audio() {
    Mix_FreeMusic(music);

    Mix_Quit();
}

/* Audio::initialize()
 *
 * Initializes SDL_mixer
 * 
 * Returns:
 * true if initialization was successful, false if there were errors
 */
bool Audio::initialize() {
    // Initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError() );
		return false;
    }

    return true;
}

/* Audio::initialize()
 *
 * Loads a music file
 * 
 * Returns:
 * true if load was successful, false if there were errors
 */
bool Audio::loadMusic(std::string filename) {
    music = Mix_LoadMUS(("sound/"+filename).c_str());
    return (music != NULL);
}


/* Audio::playMusic() 
 *
 * Plays music
 */
void Audio::playMusic() {
    Mix_PlayMusic(music, -1);
}

/* Audio::playMusic() 
 *
 * Stops music
 */
void Audio::stopMusic() {
    Mix_HaltMusic();
}