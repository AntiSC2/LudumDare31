#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <Camera/camera2D.h>
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>

class Input {
   private:
      SDL_Event event;
      static bool keys[65536];

      static std::vector<SDL_Scancode> pressedKeys;
      static std::vector<unsigned int> clickedButtons;

      bool quit = false;
      static int mx, my, mb;
      static bool mg;
   public:
      Input();
      void update();
      std::vector<SDL_Keycode> getPressedKeys();
      static bool keyPressed(SDL_Scancode key);
      static bool keyTyped(SDL_Scancode key);
      static bool mouseClicked(unsigned int button);
      static int getDX();
      static int getDY();
      static int getMouseButton();
      static bool mouseGrabbed();
      static int getMouseX(Camera2D* camera);
      static int getMouseY(Camera2D* camera);
      bool windowClosed();
};

#endif // INPUT_H_INCLUDED
