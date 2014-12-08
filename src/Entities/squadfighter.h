#ifndef SQUADFIGHTER_H_INCLUDED
#define SQUADFIGHTER_H_INCLUDED
#include "Entities/entity.h"
#include <Graphics/sprite.h>

class SquadFighter : public Entity {
   public:
      SquadFighter(glm::ivec2 position, glm::vec2 point);
      ~SquadFighter();
      void update();
      void draw(SpriteBatch* batch);
      const glm::ivec4& getBox();
      void damage();
      bool dead;
      bool createMissile;
   private:
      Sprite sprite;
      glm::vec2 centerPoint;
      glm::vec2 direction;
      float speed;
      int health;
      int timerMissile;
};

#endif // SQUADFIGHTER_H_INCLUDED
