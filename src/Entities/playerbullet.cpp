#include "Entities/playerbullet.h"

PlayerBullet::PlayerBullet(glm::ivec2 position) : speed(16.0f), direction(1, 0), left(false) {
   destRect.x = position.x;
   destRect.y = position.y;
   destRect.z = 32;
   destRect.w = 32;
   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 255, 255, 255, 255, "resources/textures/player.png");
}

PlayerBullet::~PlayerBullet() {
   ;
}

void PlayerBullet::update() {
   destRect += glm::ivec4(direction.x * speed, direction.y * speed, 0, 0);
   sprite.updatePosition(destRect.x, destRect.y);
   if(destRect.x > 1280)
      left = true;
}

void PlayerBullet::draw(SpriteBatch* batch) {
   sprite.render(batch);
}

const glm::ivec4& PlayerBullet::getBox() {
   return destRect;
}
