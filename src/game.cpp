#include "game.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Level/level.h"
#include <cstdlib>
#include <time.h>

Game::Game() : level(nullptr) {
   ;
}

Game::~Game() {
   ;
}

void Game::run() {
   init();
   gameLoop();
   quit();
}

void Game::gameLoop() {
   const double dt = 16.66666666666;
   double currentTime = SDL_GetTicks();
   double newTime;
   double frameTime;
   double accumelator = 0.0;

   unsigned int updates = 0;
   unsigned int frames = 0;
   unsigned int seconds = 0;
   while(!e.input->windowClosed()) {
      newTime = SDL_GetTicks();
      frameTime = newTime - currentTime;
      currentTime = newTime;
      accumelator += frameTime;

      while(accumelator >= dt) {
         update();
         updates++;
         accumelator -= dt;
      }

      drawGame();
      frames++;
      if(SDL_GetTicks() - seconds > 1000) {
         //printf("Updates: %d\nFrames: %d\nMouse X: %d\nMouse Y: %d\n", updates, frames, Input::getMouseX(e.camera), Input::getMouseY(e.camera));
         updates = 0;
         frames = 0;
         seconds = SDL_GetTicks();
      }
   }
}

void Game::update() {
   e.input->update();
   level->update();
   e.camera->update();
}

void Game::drawGame() {
   glActiveTexture(GL_TEXTURE0);
   e.screen->render();
 e.shaders[0]->setCameraMatrix(e.camera->getCameraMatrix());
   e.TheBatch->begin();
   level->drawLevel(e.TheBatch);
   e.TheBatch->end();
   e.TheBatch->renderDraw();
   e.screen->update();
}

void Game::init() {
   srand(time(nullptr));
   e.initSubSystems();
   e.initScreen(1280, 720 , "LudumDare 31");
   e.camera->setPosition(glm::ivec2(640, 360));
   e.initShaders("resources/shaders/Vertex.vert", "resources/shaders/Fragment.frag");
   e.initResources("resources/data/Game.data");
   level = new Level(e.camera);
   level->init("resources/data/Level.data");
}

void Game::quit() {
   delete level;
   level = nullptr;
}
