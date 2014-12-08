#ifndef ENEMYMISSILE_H_INCLUDED
#define ENEMYMISSILE_H_INCLUDED
#include "Entities/entity.h"
#include <Graphics/sprite.h>

class EnemyMissile : public Entity {
   public:
      EnemyMissile(glm::ivec2 position);
      ~EnemyMissile();
      void update();
      void draw(SpriteBatch* batch);
      void bounce();
      const glm::ivec4& getBox();
      void moveRight();
      bool dead;
      bool left;
   private:
      Sprite sprite;
      glm::vec2 direction;
};


#endif // ENEMYMISSILE_H_INCLUDED
