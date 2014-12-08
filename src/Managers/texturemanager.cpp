#include "texturemanager.h"

TextureManager::TextureManager() {
   ;
}

TextureManager::~TextureManager() {
   for(const auto& elem : textures) {
      printf("Removing texture: %s\n", elem.first.c_str());
      delete elem.second;
   }
}

Texture* TextureManager::createTexture(std::string filePath) {
   auto it = textures.find(filePath);
   if(it == textures.end()) {
      Texture* temp = new Texture;
      temp->loadTexture(filePath.c_str());
      printf("Creating new texture: %s\n", filePath.c_str());
      textures.insert(std::pair<std::string, Texture*>(filePath, temp));
      printf("Loading texture: %s\n", filePath.c_str());
      it = textures.find(filePath);
      temp = nullptr;
      return it->second;
   } else {
      //printf("Loading cached texture: %s\n", filePath.c_str());
      return it->second;
   }
   return nullptr;
}
