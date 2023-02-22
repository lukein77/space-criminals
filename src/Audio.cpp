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

    // Set volume for all channels to 25%
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);

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
 * Plays music already loaded
 */
void Audio::playMusic() {
    if (music) Mix_PlayMusic(music, -1);
}

/* Audio::playMusic() 
 *
 * Loads a music file and plays it
 * 
 * Parameters:
 * std::string filename: name of the music file.
 */
void Audio::playMusic(std::string filename) {
    if (loadMusic(filename)) {
        playMusic(); 
    } else {
        printf("Couldn't load music file \"%s\".\n", filename.c_str());
    }
}

// TODO pause resume

/* Audio::stopMusic() 
 *
 * Stops music
 */
void Audio::stopMusic() {
    Mix_HaltMusic();
}

/* Audio::addSoundToCache() 
 *
 * Loads a sound effect file that hasn't been loaded yet and inserts it into the sound cache
 *
 * Parameters:
 * std::string filename: name of the sound file
 * 
 * Returns:
 * Pointer to the Mix_Chunk containing the sound effect
 */
Mix_Chunk *Audio::addSoundToCache(std::string filename) {
    Mix_Chunk *sound = Mix_LoadWAV(("sound/"+filename).c_str());
    
    if (!sound) {
        printf("Error: %s\n", Mix_GetError());
    } else {
        audioCache.insert(std::pair<std::string, Mix_Chunk*>(filename, sound));
        printf("Done\n");
    }

    return sound;
}


/* Audio::playSound() 
 *
 * Loads a sound effect file and plays it
 *
 * Parameters:
 * std::string filename: name of the sound file
 */
void Audio::playSound(std::string filename) {

    // Searches for sound in cache, if not found loads from disk
    Mix_Chunk *sound = new Mix_Chunk;

    std::map <std::string, Mix_Chunk*> :: iterator it;
	it = audioCache.find(filename);

	if (it != audioCache.end()) {
		sound = it->second;
	} else {
		printf("Loading %s from disk... ", filename.c_str());
		sound = addSoundToCache(filename);
	}

    // Plays the sound
    Mix_PlayChannel(-1, sound, 0);
}