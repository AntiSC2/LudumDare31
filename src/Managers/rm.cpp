#include "rm.h"

void RM::init(const char* filePath) {
   std::ifstream fin(filePath);
   if(fin.is_open()) {
      std::string fileLine = "";
      bool textures = false, levels = false, sound = false, music = false;
      int c = 0;
      fin.seekg(0, fin.end);
      int length = fin.tellg();
      fin.seekg(0, fin.beg);
      while(c < length) {
         std::getline(fin, fileLine);
         if(fileLine == "#Textures") {
            textures = true;
            levels = false;
            sound = false;
            music = false;
         } else if(fileLine == "#Levels") {
            textures = false;
            levels = true;
            sound = false;
            music = false;
         } else if(fileLine == "#Sounds") {
            textures = false;
            levels = false;
            sound = true;
            music = false;
         } else if(fileLine == "#Music") {
            textures = false;
            levels = false;
            sound = false;
            music = true;
         } else if(textures == true) {
            TextureCache->createTexture(fileLine);
         } else if(sound == true) {
            SoundCache->createSound(fileLine);
         } else if(music == true) {
            MusicCache->createMusic(fileLine);
         }
         c += fileLine.size();
      }
   }
}

TextureManager* RM::TextureCache = new TextureManager;
SoundManager* RM::SoundCache = new SoundManager;
MusicManager* RM::MusicCache = new MusicManager;
