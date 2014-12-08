#ifndef PARTICE_H_INCLUDED
#define PARTICE_H_INCLUDED
#include <glm/glm.hpp>

class SpriteBatch;

class Particle {
   public:
      Particle(glm::ivec2 pos);
      void draw(SpriteBatch* batch);
      void update();
      bool dead;
   private:
      glm::ivec2 position;
      int length;
      int alpha;
};

#endif // PARTICE_H_INCLUDED
