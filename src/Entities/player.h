#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "Entities/entity.h"
#include <Graphics/sprite.h>

class Player : public Entity {
   public:
      Player();
      ~Player();
      void init(int x, int y);
      void update();
      void draw(SpriteBatch* batch);
      int returnY();
      bool createBullet;
      bool createShield;
      bool destroyCrystals;
      int shieldCoolDown;
   private:
      Sprite sprite;
      int speed;
      int bulletTimer;
      int crystalCoolDown;
};

#endif // PLAYER_H_INCLUDED
