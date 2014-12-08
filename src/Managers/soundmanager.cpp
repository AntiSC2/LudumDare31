#include "soundmanager.h"


SoundManager::SoundManager() {
   ;
}

SoundManager::~SoundManager() {
   for(const auto& elem : sounds) {
      printf("Removing sound: %s\n", elem.first.c_str());
      Mix_FreeChunk(elem.second);
   }
}

Mix_Chunk* SoundManager::createSound(std::string filePath) {
   auto it = sounds.find(filePath);
   if(it == sounds.end()) {
      Mix_Chunk* temp = Mix_LoadWAV(filePath.c_str());
      printf("Creating new sound: %s\n", filePath.c_str());
      sounds.insert(std::pair<std::string, Mix_Chunk*>(filePath, temp));
      printf("Loading sound: %s\n", filePath.c_str());
      it = sounds.find(filePath);
      temp = nullptr;
      return it->second;
   } else {
      //printf("Loading cached sound: %s\n", filePath.c_str());
      return it->second;
   }
   return nullptr;
}
