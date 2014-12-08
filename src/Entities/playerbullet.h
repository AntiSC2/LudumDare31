#ifndef PLAYERBULLET_H_INCLUDED
#define PLAYERBULLET_H_INCLUDED
#include "Entities/entity.h"
#include <Graphics/sprite.h>

class SpriteBatch;

class PlayerBullet : public Entity {
   public:
      PlayerBullet(glm::ivec2 position);
      ~PlayerBullet();
      void update();
      void draw(SpriteBatch* batch);
      bool left;
      const glm::ivec4& getBox();
   private:
      Sprite sprite;
      glm::vec2 direction;
      float speed;
};

#endif // PLAYERBULLET_H_INCLUDED
