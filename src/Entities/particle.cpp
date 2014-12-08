#include "Entities/partice.h"
#include <Managers/rm.h>
#include <Graphics/spritebatch.h>
#include <SDL2/SDL_mixer.h>

Particle::Particle(glm::ivec2 pos) : dead(false), length(1), alpha(255) {
   position = pos;
}

void Particle::update() {
   if(length != 60)
      length += 1;
   else
      dead = true;
   alpha -= 4;
}

void Particle::draw(SpriteBatch* batch) {
   batch->draw(glm::vec4(position.x - 8, position.y - length, 16, length), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/white.png")->getID(), 0.0f, Color(100, 255, 255, alpha));
   batch->draw(glm::vec4(position.x - 8, position.y, 16, length), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/white.png")->getID(), 0.0f, Color(100, 255, 255, alpha));
   batch->draw(glm::vec4(position.x, position.y - 8, length, 16), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/white.png")->getID(), 0.0f, Color(100, 255, 255, alpha));
   batch->draw(glm::vec4(position.x - length, position.y - 8, length, 16), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/white.png")->getID(), 0.0f, Color(100, 255, 255, alpha));
}
