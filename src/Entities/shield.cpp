#include "shield.h"

Shield::Shield(glm::ivec2 position) : dead(false), timer(300)  {
   destRect = glm::ivec4(position.x, position.y, 32, 256);
   sprite.initSprite(destRect.x - 8, destRect.y - 12, destRect.z + 16, destRect.w + 32, 255, 255, 255, 255, "resources/textures/shield.png");
}

Shield::~Shield() {
   ;
}

void Shield::update() {
   if(timer == 0)
      dead = true;
   else
      timer--;
}

void Shield::draw(SpriteBatch* batch) {
   sprite.render(batch);
}

const glm::ivec4& Shield::getBox() {
   return destRect;
}
