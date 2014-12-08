#ifndef RM_H_INCLUDED
#define RM_H_INCLUDED
#include "texturemanager.h"
#include "soundmanager.h"
#include "musicmanager.h"
#include <fstream>
#include <string>

class RM {
   public:
      static void init(const char* filePath);
      static TextureManager* TextureCache;
      static SoundManager* SoundCache;
      static MusicManager* MusicCache;

   private:
};

#endif // RM_H_INCLUDED
