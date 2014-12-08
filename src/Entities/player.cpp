#include "player.h"
#include <Input.h>

Player::Player() : speed(5), createBullet(false), createShield(false), destroyCrystals(false), shieldCoolDown(0) {
   destRect.z = 128;
   destRect.w = 128;
}

Player::~Player() {
   ;
}

void Player::init(int x, int y) {
   destRect.x = x;
   destRect.y = y;
   sprite.initSprite(destRect.x, destRect.y, destRect.z, destRect.w, 255, 255, 255, 255, "resources/textures/player.png");
}

void Player::update() {
   if(Input::keyPressed(SDL_SCANCODE_UP))
      destRect.y -= speed;
   else if(Input::keyPressed(SDL_SCANCODE_DOWN)) {
      destRect.y += speed;
   }
   if(createShield == false) {
      if(Input::keyTyped(SDL_SCANCODE_A) && shieldCoolDown == 0)
         createShield = true;
   } else if(Input::mouseClicked(3) || Input::keyTyped(SDL_SCANCODE_A)) {
      createShield = false;
   }

   if(Input::keyTyped(SDL_SCANCODE_S) && crystalCoolDown == 0) {
      crystalCoolDown = 7200;
      destroyCrystals = true;
   }

   if(Input::keyPressed(SDL_SCANCODE_SPACE) && bulletTimer == 0 && createBullet == false) {
      createBullet = true;
      bulletTimer = 30;
   }
   if(destRect.y < 0)
      destRect.y = 0;
   else if(destRect.y + destRect.w > 720)
      destRect.y = 720 - destRect.w;

   sprite.updatePosition(destRect.x, destRect.y);
   if(bulletTimer > 0)
      bulletTimer--;
   if(shieldCoolDown > 0)
      shieldCoolDown--;
   if(crystalCoolDown > 0)
      crystalCoolDown--;
}

void Player::draw(SpriteBatch* batch) {
   sprite.render(batch);
}
