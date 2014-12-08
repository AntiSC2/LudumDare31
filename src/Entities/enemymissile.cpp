#include "enemymissile.h"

EnemyMissile::EnemyMissile(glm::ivec2 position) : dead(false), left(false) {
   destRect = glm::ivec4(position.x, position.y, 32, 32);
   direction.x = -1;
   direction.y = 0;
   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 255, 255, 255, 255, "resources/textures/enemymissile.png");
}

EnemyMissile::~EnemyMissile() {
   ;
}

void EnemyMissile::update() {
   if(destRect.x < 250) {
      left = true;
   } else if((destRect.x + destRect.z) > 1280) {
      bounce();
   }
   destRect += glm::ivec4(direction.x * 4, direction.y * 3, 0, 0);
   sprite.updatePosition(destRect.x, destRect.y);
}

void EnemyMissile::draw(SpriteBatch* batch) {
   sprite.render(batch);
}

void EnemyMissile::bounce() {
   direction.x = -direction.x;
}

const glm::ivec4& EnemyMissile::getBox() {
   return destRect;
}

void EnemyMissile::moveRight() {
   destRect.x++;
}
