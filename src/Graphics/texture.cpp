#include "texture.h"

Texture::Texture() : ID(0), width(0), height(0) {

}

Texture::~Texture() {
   if(ID != 0) {
      glDeleteTextures(1, &ID);
   }
}

GLuint Texture::currentlyBound = 0;

void Texture::loadTexture(const char *filePath) {
   if(ID != 0) {
      glDeleteTextures(1, &ID);
   }
   //Generating the texture itself
   glGenTextures(1, &ID);
   glBindTexture(GL_TEXTURE_2D, ID);
   //Specify simple parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   //Generate the mip map
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   //Loading in the image
   SDL_Surface *surface = IMG_Load(filePath);
   if(surface == nullptr || surface == NULL) {
      printf("Failed to load image file %s!\n", filePath);
      printf("Could not create texture! Missing Image!\n");
   }
   //Upload the data to the GPU
   width = surface->w;
   height = surface->h;
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
   //Create mipmap for the texture
   glGenerateMipmap(GL_TEXTURE_2D);
   //Clean up
   SDL_FreeSurface(surface);
   glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::use() {
   if(currentlyBound != ID) {
      glBindTexture(GL_TEXTURE_2D, ID);
      currentlyBound = ID;
   }
}

void Texture::unuse() {
   glBindTexture(GL_TEXTURE_2D, 0);
   currentlyBound = 0;
}

GLuint Texture::getID() {
   return ID;
}
