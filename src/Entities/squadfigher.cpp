#include "squadfighter.h"
#include <glm/gtx/rotate_vector.hpp>

SquadFighter::SquadFighter(glm::ivec2 position, glm::vec2 point) : dead(false), createMissile(false), centerPoint(point), speed(6.0f), health(5), timerMissile(120) {
   direction.x = -1;
   direction.y = 0;
   destRect = glm::ivec4(position.x, position.y, 128, 128);
   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 255, 255, 255, 255, "resources/textures/squadfighter.png");
}

SquadFighter::~SquadFighter() {
   ;
}

void SquadFighter::update() {
   if(health <= 0) {
      dead = true;
   }
   glm::vec2 temp = glm::normalize(centerPoint - glm::vec2(destRect.x, destRect.y));
   if(glm::length(centerPoint - glm::vec2(destRect.x, destRect.y)) < 32.0f) {
      direction = glm::rotate(direction, 10.0f);
   } else {
      direction = temp;
   }
   destRect += glm::vec4(direction.x * speed, direction.y * speed, 0.0f, 0.0f);
   sprite.updatePosition(destRect.x, destRect.y);
   if(timerMissile > 0) {
      timerMissile--;
   } else {
      timerMissile = 240;
      createMissile = true;
   }
}

void SquadFighter::draw(SpriteBatch* batch) {
   sprite.render(batch);
}

const glm::ivec4& SquadFighter::getBox() {
   return destRect;
}

void SquadFighter::damage() {
   health--;
}
