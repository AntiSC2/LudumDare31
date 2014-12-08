#include "enemycrystal.h"

EnemyCrystal::EnemyCrystal(glm::ivec4 position, glm::vec2 dir) : speed (6.0f), entered(false), left(false)  {
   destRect = position;
   direction = dir;
   direction = glm::normalize(direction - glm::vec2(destRect.x, destRect.y));
   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 255, 255, 255, 255, "resources/textures/crystal.png");
}

EnemyCrystal::~EnemyCrystal() {
   ;
}

void EnemyCrystal::update() {
   if(entered == false && destRect.x + destRect.z < 1280) {
      entered = true;
   }
   destRect += glm::vec4(direction.x * speed, direction.y * speed, 0, 0);
   sprite.updatePosition(destRect.x, destRect.y);
   if(destRect.y < 0) {
      direction.y = -direction.y;
      while(destRect.y < 0) {
         destRect.y++;
      }
   }
   else if(destRect.y + destRect.w > 720) {
      direction.y = -direction.y;
      while(destRect.y + destRect.w > 720) {
         destRect.y--;
      }
   }
   if(destRect.x < 250) {
      left = true;
   } else if(destRect.x + destRect.z > 1280 && entered == true) {
      bounce();
   }

}

void EnemyCrystal::draw(SpriteBatch* batch) {
   sprite.render(batch);
}

void EnemyCrystal::bounce() {
   direction.x = -direction.x;
}

const glm::ivec4& EnemyCrystal::getBox() {
   return destRect;
}

void EnemyCrystal::moveRight() {
   destRect.x++;
}
