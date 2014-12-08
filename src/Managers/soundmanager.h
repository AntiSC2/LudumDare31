#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <SDL2/SDL_mixer.h>
#include <map>
#include <utility>
#include <stdio.h>
#include <string>

class SoundManager {
   public:
      SoundManager();
      ~SoundManager();

      Mix_Chunk* createSound(std::string);
   private:
      std::map<std::string, Mix_Chunk*> sounds;
};

#endif // SOUNDMANAGER_H_INCLUDED
