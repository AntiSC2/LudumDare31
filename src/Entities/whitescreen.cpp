#include "whitescreen.h"
#include <glm/glm.hpp>
#include <Managers/rm.h>
#include <Graphics/vertex.h>
#include <Graphics/spritebatch.h>

WhiteScreen::WhiteScreen() : alpha(0), started(false) {
   ;
}

WhiteScreen::~WhiteScreen() {
   ;
}

void WhiteScreen::update() {
   if(alpha == 255)
      started = false;
   if(started) {
      if(alpha < 250) {
         alpha += 50;
      } else if(alpha == 250) {
         alpha += 5;
      }
   } else if(alpha > 0)
      alpha--;
}

void WhiteScreen::draw(SpriteBatch* batch) {
   batch->draw(glm::vec4(0, 0, 1280, 720), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/white.png")->getID(), 0.0f, Color(255, 255, 255, alpha));
}

void WhiteScreen::start() {
   started = true;
}
