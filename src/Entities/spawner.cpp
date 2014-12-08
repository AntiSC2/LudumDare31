#include "spawner.h"
#include <cstdlib>

Spawner::Spawner(int y) : spawn(false), dead(false), left(false), health(5), spawnTimer(240) {
   destRect.y = y;
   destRect.x = 1280;
   destRect.z = 256;
   destRect.w = 256;
   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 255, 255, 255, 255, "resources/textures/spawner.png");
}

Spawner::~Spawner() {
   ;
}

void Spawner::update() {
   if(health <= 0) {
      dead = true;
   }
   destRect.x -= 1;
   if(destRect.x < 250)
      left = true;
   sprite.updatePosition(destRect.x, destRect.y);
   if(spawnTimer > 0) {
      spawnTimer--;
   } else {
      spawn = true;
      spawnTimer = 120;
   }
}

void Spawner::draw(SpriteBatch* batch) {
   sprite.render(batch);
}

void Spawner::damage() {
   health--;
}

const glm::ivec4& Spawner::getBox() {
   return destRect;
}
