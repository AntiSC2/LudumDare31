#include "input.h"

Input::Input() {
   for (unsigned int i = 0; i < 65536; i++) {
      keys[i] = false;
   }
}

bool Input::keys[65536];
std::vector<SDL_Scancode> Input::pressedKeys;
std::vector<unsigned int> Input::clickedButtons;
int Input::mx;
int Input::my;
int Input::mb;
bool Input::mg = false;

void Input::update() {
   while (SDL_PollEvent(&event)) {
      switch (event.type) {
         case SDL_QUIT:
            quit = true;
            break;
         case SDL_KEYDOWN:
            keys[event.key.keysym.scancode] = true;
            break;
         case SDL_KEYUP:
            keys[event.key.keysym.scancode] = false;
            if (!pressedKeys.empty() && std::find(pressedKeys.begin(), pressedKeys.end(), event.key.keysym.scancode) != pressedKeys.end()) {
               pressedKeys.erase(std::find(pressedKeys.begin(), pressedKeys.end(), event.key.keysym.scancode));
            }
            break;
         case SDL_MOUSEBUTTONDOWN:
            mb = event.button.button;
            break;
         case SDL_MOUSEBUTTONUP:
            mb = 0;
            if (!clickedButtons.empty() && std::find(clickedButtons.begin(), clickedButtons.end(), event.button.button) != clickedButtons.end()) {
               clickedButtons.erase(std::find(clickedButtons.begin(), clickedButtons.end(), event.button.button));
            }
            break;
      }
   }
   SDL_GetMouseState(&mx, &my);

   /*if (key_pressed(SDL_SCANCODE_ESCAPE)) {
      mg = false;
      SDL_ShowCursor(SDL_ENABLE);
   }
   if (!mg && Input::get_mouse_button() == SDL_BUTTON_LEFT) {
      mg = true;
      SDL_ShowCursor(SDL_DISABLE);
   }*/
}

bool Input::keyPressed(SDL_Scancode key) {
   return keys[key];
}

bool Input::keyTyped(SDL_Scancode key) {
   bool pressed = keyPressed(key);
   if (!pressed) return false;
   if(!pressedKeys.empty() && std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end()) {
      return false;
   }
   pressedKeys.push_back(key);
   return true;
}

bool Input::mouseClicked(unsigned int button) {
   bool clicked = mb == button;
   if (!clicked) return false;
   if(!clickedButtons.empty() && std::find(clickedButtons.begin(), clickedButtons.end(), button) != clickedButtons.end()) {
      return false;
   }
   clickedButtons.push_back(button);
   return true;
}

int Input::getMouseButton() {
   return mb;
}

bool Input::mouseGrabbed() {
   return mg;
}

std::vector<int> Input::getPressedKeys() {
   std::vector<int> result;
   for (unsigned int i = 0; i < 65536; i++) {
      if (keys[i]) result.push_back(i);
   }
   return result;
}

int Input::getDX() {
   return 1280 / 2 - mx;
}

int Input::getDY() {
   return 720 / 2 - my;
}

int Input::getMouseX(Camera2D* camera) {
   int mouseX = camera->getPosition().x;
   return mx - (camera->getWidth() / 2) + mouseX;
}

int Input::getMouseY(Camera2D* camera) {
   int mouseY = camera->getPosition().y;
   return (my - (camera->getHeight() / 2) + mouseY);
}

bool Input::windowClosed() {
   return quit;
}
