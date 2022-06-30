#ifndef _AUDIO_H_INCLUDED_
#define _AUDIO_H_INCLUDED_

#include "common.h"

class Audio {
    private:
        Mix_Music *music;

    public:
        Audio();
        ~Audio();
        
        bool initialize();
        bool loadMusic(std::string filename);
        bool loadSoundEffect(std::string filename);

        void playMusic();
        void stopMusic();
};

#endif