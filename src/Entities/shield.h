#ifndef SHIELD_H_INCLUDED
#define SHIELD_H_INCLUDED
#include "Entities/entity.h"
#include <Graphics/sprite.h>

class Shield : public Entity {
   public:
      Shield(glm::ivec2 position);
      ~Shield();
      void update();
      void draw(SpriteBatch* batch);
      bool dead;
      const glm::ivec4& getBox();
   private:
      Sprite sprite;
      int timer;
};


#endif // SHIELD_H_INCLUDED
