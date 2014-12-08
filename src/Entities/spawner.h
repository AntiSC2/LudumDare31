#ifndef SPAWNER_H_INCLUDED
#define SPAWNER_H_INCLUDED
#include "Entities/entity.h"
#include <Graphics/sprite.h>

class Spawner : public Entity {
   public:
      Spawner(int y);
      ~Spawner();
      void update();
      void draw(SpriteBatch* batch);
      void damage();
      const glm::ivec4& getBox();
      bool spawn;
      bool dead;
      bool left;
   private:
      Sprite sprite;
      int spawnTimer;
      int health;
};

#endif // SPAWNER_H_INCLUDED
