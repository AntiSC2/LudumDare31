#include "musicmanager.h"

MusicManager::MusicManager() {
   ;
}

MusicManager::~MusicManager() {
   for(const auto& elem : music) {
      printf("Removing music: %s\n", elem.first.c_str());
      Mix_FreeMusic(elem.second);
   }
}

Mix_Music* MusicManager::createMusic(std::string filePath) {
   auto it = music.find(filePath);
   if(it == music.end()) {
      Mix_Music* temp = Mix_LoadMUS(filePath.c_str());
      printf("Creating new music: %s\n", filePath.c_str());
      music.insert(std::pair<std::string, Mix_Music*>(filePath, temp));
      printf("Loading music: %s\n", filePath.c_str());
      it = music.find(filePath);
      temp = nullptr;
      return it->second;
   } else {
      //printf("Loading cached music: %s\n", filePath.c_str());
      return it->second;
   }
   return nullptr;
}
