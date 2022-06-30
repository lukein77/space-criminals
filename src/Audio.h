#ifndef _AUDIO_H_INCLUDED_
#define _AUDIO_H_INCLUDED_

#include "common.h"
#include <map>

class Audio {
    private:
        Mix_Music *music;

        std::map <std::string, Mix_Chunk*> audioCache;

        void clearAudioCache();
        Mix_Chunk *addSoundToCache(std::string filename);

    public:
        Audio();
        ~Audio();
        
        bool initialize();
        bool loadMusic(std::string filename);
        bool loadSound(std::string filename);

        void playMusic();
        void playMusic(std::string filename);
        void pauseMusic();
        void stopMusic();
        void playSound(std::string filename);
};

#endif