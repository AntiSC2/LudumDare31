#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <Engine.h>

class Level;

class Game {
   public:
      Game();
      ~Game();
      void run();
      Engine e;
   private:
      void gameLoop();
      void update();
      void drawGame();
      void init();
      void quit();
      Level* level;
};

#endif // GAME_H_INCLUDED
