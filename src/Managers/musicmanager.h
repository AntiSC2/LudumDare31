#ifndef MUSICMANAGER_H_INCLUDED
#define MUSICMANAGER_H_INCLUDED

#include <SDL2/SDL_mixer.h>
#include <map>
#include <utility>
#include <stdio.h>
#include <string>

class MusicManager {
   public:
      MusicManager();
      ~MusicManager();

      Mix_Music* createMusic(std::string);
   private:
      std::map<std::string, Mix_Music*> music;
};

#endif // MUSICMANAGER_H_INCLUDED
