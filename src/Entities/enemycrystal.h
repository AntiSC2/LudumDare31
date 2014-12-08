#ifndef ENEMYCRYSTAL_H_INCLUDED
#define ENEMYCRYSTAL_H_INCLUDED

#include "Entities/entity.h"
#include <Graphics/sprite.h>
#include <glm/glm.hpp>

class EnemyCrystal : public Entity {
   public:
      EnemyCrystal(glm::ivec4 position, glm::vec2 dir);
      ~EnemyCrystal();
      void update();
      void draw(SpriteBatch* batch);
      void bounce();
      const glm::ivec4& getBox();
      void moveRight();
      bool left;
   private:
      Sprite sprite;
      glm::vec2 direction;
      float speed;
      bool entered;
};

#endif // ENEMYCRYSTAL_H_INCLUDED
