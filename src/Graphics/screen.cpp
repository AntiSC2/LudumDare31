#include "screen.h"

Screen::Screen(int width, int height, const char* title) {
   window = nullptr;
   this->width = width;
   this->height = height;
   window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
   initGL();
}

Screen::~Screen() {
   SDL_DestroyWindow(window);
   window = nullptr;
}

void Screen::initGL() {
   //Sets some basic OpenGL attributes
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3);
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
   SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 3);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


   if(SDL_GL_CreateContext(window) == nullptr)
   {
      printf("Could not create OpenGL context! SDL Error: %s", SDL_GetError());
   }

   GLenum err = glewInit();

   if(err != GLEW_OK)
   {
      printf("Could not initialize GLEW! GLEW ERROR: %s", glewGetErrorString(err));
   }
   else
   {

      printf("OpenGL Version %s\n", glGetString(GL_VERSION));

      glEnable (GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   }
}

void Screen::render() {
   glClearDepth(1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::update() {
   GLenum err;
   while ((err = glGetError()) != GL_NO_ERROR)
   {
      //printf("Error while rendering! GLEW ERROR: %s\n", glGetString(err));
   }

   SDL_GL_SwapWindow(window);
}

int Screen::getWidth() {
   return width;
}

int Screen::getHeight() {
   return height;
}

