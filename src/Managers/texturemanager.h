#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED
#include <map>
#include <utility>
#include <stdio.h>
#include <string>
#include "Graphics/texture.h"

class TextureManager {
   public:
      TextureManager();
      ~TextureManager();

      Texture* createTexture(std::string);
   private:
      std::map<std::string, Texture*> textures;
};

#endif // TEXTUREMANAGER_H_INCLUDED
