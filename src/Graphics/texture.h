#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

class Texture {
   public:
      Texture();
      ~Texture();

      void loadTexture(const char* filePath);

      void use();
      void unuse();

      GLuint getID();

      static GLuint currentlyBound;

   private:
      GLuint width, height;
      GLuint ID;
};

#endif // TEXTURE_H_INCLUDED
