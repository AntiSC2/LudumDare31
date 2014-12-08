#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include <glm/glm.hpp>

class SpriteBatch;

class Entity {
   public:
      virtual ~Entity() {
         ;
      }
      virtual void update() = 0;
      virtual void draw(SpriteBatch* batch) = 0;
      const glm::ivec2& getPosition() {
         return glm::ivec2(destRect.x, destRect.y);
      }
   protected:
      glm::ivec4 destRect;
};

#endif // ENTITY_H_INCLUDED
