#include "level.h"
#include <glm/glm.hpp>
#include <Graphics/vertex.h>
#include <Managers/rm.h>
#include <input.h>
#include "Entities/shield.h"
#include <Graphics/vertex.h>
#include <string>
#include <SDL2/SDL_mixer.h>

int numDigits(int number)
{
   int digits = 0;
   if (number < 0) digits = 1; // remove this line if '-' counts as a digit
   while (number) {
      number /= 10;
      digits++;
   }
   return digits;
}

Level::Level(Camera2D* camera) : levelCamera(camera), timerCrystal(0), timerSquadFighter(0),
   shield(nullptr), score(0), healthBase(10), spawnTimer(0), gameState(GAMESTATE::MENU), shake(false), shakeTimer(0), showScore(0), once(false) {
   ;
}

Level::~Level() {
   if(shield != nullptr)
      delete shield;
}

void Level::init(const char* filePath) {
   levelBatch.init();
   levelBatch.begin();
   levelBatch.draw(glm::vec4(0, 0, 1280, 720), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/background.png")->getID(), 0.0f, Color(255, 255, 255, 255));
   levelBatch.end();
   player.init(100, 296);
}

void Level::update() {
   ///GAMEPLAY
   if(music == true) {
      if(Mix_PlayingMusic() == 0)
         Mix_PlayMusic(RM::MusicCache->createMusic("resources/music/soundtrack.wav"), -1);
   } else if(Mix_PlayingMusic() != 0)
      Mix_HaltMusic();
   int defaultShake = 30;
   if(gameState == GAMESTATE::PLAY) {
      once = true;
      if(spawnTimer > 0) {
         spawnTimer--;
      } else {
         int yRand = rand() % 464;
         spawnTimer = 900;
         spawners.emplace_back(yRand);
      }
      if(shakeTimer > 0) {
         shake = true;
         if(shakeTimer == defaultShake && sound == true)
            Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/TakingDamage.wav"), 0);
         shakeTimer--;
      } else {
         shake = false;
         levelCamera->setPosition(glm::vec2(640, 360));
      }
      if(shake == true) {
         int xRand = rand()%32;
         int yRand = rand()%32;
         xRand -= 16;
         yRand -= 16;
         levelCamera->setPosition(glm::vec2(640 + xRand, 360 + yRand));
      }
      if(healthBase <= 0) {
         gameState = GAMESTATE::MENU;
         showScore = score;
         restart();
      }
      if(timerCrystal == 0) {
         glm::ivec4 temp2(1280, rand() % 720, 64, 64);
         glm::vec2 dirTemp(200, rand() % 720);
         enemyCrystals.emplace_back(temp2, dirTemp);
         timerCrystal = rand() % 480;
         timerCrystal += 15;
      } else {
         timerCrystal--;
      }
      if(timerSquadFighter == 0) {
         glm::ivec2 temp(1280, rand() % 720);
         glm::ivec2 pointtemp(rand() % 500, rand() % 320);
         glm::vec2 point(pointtemp.x + 400, pointtemp.y + 200);
         squadFighters.emplace_back(temp, point);
         timerSquadFighter = rand() % 300;
         timerSquadFighter += 120;
      } else {
         timerSquadFighter--;
      }
      player.update();
      if(player.createBullet == true) {
         player.createBullet = false;
         glm::ivec2 temp;
         temp.x = 100;
         temp.y = player.getPosition().y + 64;
         if(sound == true) {
            Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/PlayerShoot.wav"), 0);
         }
         printf("%d\n%d\n", temp.x, temp.y);
         playerBullets.emplace_back(temp);
      }
      if(player.createShield == true) {
         if(Input::mouseClicked(1) && shield == nullptr) {
            if(sound == true)
               Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/Shield.wav"), 0);
            shield = new Shield(glm::ivec2(Input::getMouseX(levelCamera) - 16, Input::getMouseY(levelCamera) - 128));
            player.createShield = false;
            player.shieldCoolDown = 900;
         }
      }
      if(player.destroyCrystals == true) {
         if(sound == true)
            Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/nuke.wav"), 0);
         player.destroyCrystals = false;
         enemyCrystals.clear();
         explosion.start();
      }
      if(shield != nullptr) {
         shield->update();
         if(shield->dead) {
            delete shield;
            shield = nullptr;
         }
      }
      for(int i = 0; i < playerBullets.size(); i++) {
         playerBullets[i].update();
         if(playerBullets[i].left == true) {
            playerBullets[i] = playerBullets.back();
            playerBullets.pop_back();
            i--;
         } else {
            collideWithCrystals(playerBullets[i]);
            if(collideWithSquad(playerBullets[i]) || collideWithSpawners(playerBullets[i])) {
               if(sound == true)
                  Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/Hit.wav"), 0);
               playerBullets[i] = playerBullets.back();
               playerBullets.pop_back();
               i--;
            }
            collideWithMissiles(playerBullets[i]);
         }
      }
      for(int i = 0; i < enemyCrystals.size(); i++) {
         enemyCrystals[i].update();
         if(shield != nullptr && collision(enemyCrystals[i].getBox(), shield->getBox())) {
            enemyCrystals[i].bounce();
            while(collision(enemyCrystals[i].getBox(), shield->getBox())) {
               enemyCrystals[i].moveRight();
            }
         }
         if(enemyCrystals[i].left == true) {
            particles.emplace_back(glm::ivec2(enemyCrystals[i].getPosition().x + 32, enemyCrystals[i].getPosition().y + 32));
            enemyCrystals[i] = enemyCrystals.back();
            healthBase--;
            shakeTimer = defaultShake;
            enemyCrystals.pop_back();
            if(sound == true)
               Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/EnemyDead.wav"), 0);
            i--;
         }
      }
      for(int i = 0; i < squadFighters.size(); i++) {
         squadFighters[i].update();
         if(squadFighters[i].dead) {
            particles.emplace_back(glm::ivec2(squadFighters[i].getPosition().x + 64, squadFighters[i].getPosition().y + 64));
            squadFighters[i] = squadFighters.back();
            squadFighters.pop_back();
            score += 10;
            if(sound == true)
                Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/EnemyDead.wav"), 0);
            i--;
         } else if(squadFighters[i].createMissile) {
            glm::ivec2 temp = squadFighters[i].getPosition();
            temp.x += 32;
            temp.y += 32;
            enemyMissiles.emplace_back(temp);
            squadFighters[i].createMissile = false;
         }
      }
      for(int i = 0; i < enemyMissiles.size(); i++) {
         enemyMissiles[i].update();
         if(shield != nullptr && collision(enemyMissiles[i].getBox(), shield->getBox())) {
            enemyMissiles[i].bounce();
            while(collision(enemyMissiles[i].getBox(), shield->getBox())) {
               enemyMissiles[i].moveRight();
            }
         } else if(enemyMissiles[i].dead) {
            particles.emplace_back(glm::ivec2(enemyMissiles[i].getPosition().x + 8, enemyMissiles[i].getPosition().y + 8));
            enemyMissiles[i] = enemyMissiles.back();
            score += 1;
            enemyMissiles.pop_back();
            if(sound == true)
               Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/EnemyDead.wav"), 0);
            i--;
         } else if(enemyMissiles[i].left) {
            particles.emplace_back(glm::ivec2(enemyMissiles[i].getPosition().x + 8, enemyMissiles[i].getPosition().y + 8));
            enemyMissiles[i] = enemyMissiles.back();
            healthBase--;
            shakeTimer = defaultShake;
            enemyMissiles.pop_back();
            if(sound == true)
               Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/EnemyDead.wav"), 0);
            i--;
         }
      }
      for(int i = 0; i < spawners.size(); i++) {
         spawners[i].update();
         if(spawners[i].spawn == true) {
            spawners[i].spawn = false;
            glm::ivec4 temp2(spawners[i].getPosition().x + 96, spawners[i].getPosition().y + 96, 64, 64);
            glm::vec2 dirTemp(200, rand() % 720);
            enemyCrystals.emplace_back(temp2, dirTemp);
         }
         if(spawners[i].left == true) {
            gameState = GAMESTATE::MENU;
            //Mix_PlayChannel(-1, RM::SoundCache->createSound("resource/sounds/nuke.wav"), 0);
            restart();
         }
         if(spawners[i].dead == true) {
            particles.emplace_back(glm::ivec2(spawners[i].getPosition().x + 126, spawners[i].getPosition().y + 126 ));
            spawners[i] = spawners.back();
            spawners.pop_back();
            if(sound == true)
               Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/EnemyDead.wav"), 0);
            i--;
         }
      }
      for(int i = 0; i < particles.size(); i++) {
         particles[i].update();
         if(particles[i].dead == true) {
            particles[i] = particles.back();
            particles.pop_back();
            i--;
         }
      }
      explosion.update();
      if(Input::keyTyped(SDL_SCANCODE_ESCAPE)) {
         showScore = score;
         levelCamera->setPosition(glm::vec2(640, 360));
         gameState = GAMESTATE::MENU;
         restart();
      }
   } else {
      levelCamera->setPosition(glm::vec2(640, 360));
      if(Input::mouseClicked(1) && Input::getMouseX(levelCamera) >= 1024 && Input::getMouseY(levelCamera) >= 550)
         gameState = GAMESTATE::PLAY;
   }
   if(Input::keyTyped(SDL_SCANCODE_N)) {
      if(sound == true)
         sound = false;
      else
         sound = true;
   }
   if(Input::keyTyped(SDL_SCANCODE_M)) {
      if(music == true)
         music = false;
      else
         music = true;
   }
}

void Level::drawLevel(SpriteBatch* batch) {
   levelBatch.renderDraw();
   if(gameState == GAMESTATE::PLAY) {
      player.draw(batch);
      if(shield != nullptr) {
         shield->draw(batch);
      } else if(player.createShield == true) {
         batch->draw(glm::vec4(Input::getMouseX(levelCamera) - 24, Input::getMouseY(levelCamera) - 140, 48, 288),
                     glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/shield.png")->getID(),
                     0.0f, Color(255, 255, 255, 128));
      }
      for(int i = 0; i < playerBullets.size(); i++) {
         playerBullets[i].draw(batch);
      }
      for(int i = 0; i < enemyCrystals.size(); i++) {
         enemyCrystals[i].draw(batch);
      }
      for(int i = 0; i < squadFighters.size(); i++) {
         squadFighters[i].draw(batch);
      }
      for(int i = 0; i < enemyMissiles.size(); i++) {
         enemyMissiles[i].draw(batch);
      }
      for(int i = 0; i < spawners.size(); i++) {
         spawners[i].draw(batch);
      }
      for(int i = 0; i < particles.size(); i++) {
         particles[i].draw(batch);
      }
      int yHealth = 0;
      for(int i = 0; i < healthBase; i++) {
         batch->draw(glm::vec4(100, 0 + yHealth, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/health.png")->getID(), 0.0f, Color(255, 255, 255, 255));
         yHealth+=64;
      }
      explosion.draw(batch);
   } else {
      batch->draw(glm::vec4(0, 0, 1280, 720),
                  glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/black.png")->getID(),
                  0.0f, Color(255, 255, 255, 128));
      batch->draw(glm::vec4(1024, 550, 256, 256), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                  RM::TextureCache->createTexture("resources/textures/menu_buttons.png")->getID(),
                  0.0f, Color(255, 255, 255, 255));
      batch->draw(glm::vec4(0, 0, 1280, 720), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/tutorial.png")->getID(), 0.0f, Color(255, 255, 255, 255));
      if(once == true) {
         batch->draw(glm::vec4(0, 0, 1280, 720), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/gameover.png")->getID(), 0.0f, Color(255, 255, 255, 255));
         batch->draw(glm::vec4(364, 250, 256, 256), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/score.png")->getID(), 0.0f, Color(255, 255, 255, 255));
         int lengthOfScore = numDigits(showScore);
         int offset = 36;
         int x = 0;
         for(int i = 0; i < lengthOfScore; i++) {
            std::string temp(std::to_string(showScore));
            if(temp[i] == '0')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/zero.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '1')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/one.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '2')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/two.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '3')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/three.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '4')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/four.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '5')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/five.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '6')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/six.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '7')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/seven.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '8')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/eight.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            else if(temp[i] == '9')
               batch->draw(glm::vec4(604 + x, 350, 64, 64), glm::vec4(0, 0, 1, 1), RM::TextureCache->createTexture("resources/textures/nine.png")->getID(), 0.0f, Color(255, 255, 255, 255));
            x += offset;
         }
      }
   }
}

void Level::collideWithCrystals(PlayerBullet& bullet) {
   int index = 0;
   if(enemyCrystals.size() > 0) {
      glm::vec2 objPos(bullet.getPosition());
      glm::vec2 temp(enemyCrystals[0].getPosition());
      float distance = glm::length(objPos - temp);
      for(int i = 1; i < enemyCrystals.size(); i++) {
         temp = enemyCrystals[i].getPosition();
         if(glm::length(objPos - temp) < distance) {
            distance = glm::length(objPos - temp);
            index = i;
         }
      }
      if(collision(bullet.getBox(), enemyCrystals[index].getBox())) {
         particles.emplace_back(glm::ivec2(enemyCrystals[index].getPosition().x + 32, enemyCrystals[index].getPosition().y + 32));
         enemyCrystals[index] = enemyCrystals.back();
         enemyCrystals.pop_back();
         if(sound == true)
            Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/EnemyDead.wav"), 0);
         score += 2;
      }
   }
}

bool Level::collideWithSquad(PlayerBullet& bullet) {
   int index = 0;
   if(squadFighters.size() > 0) {
      glm::vec2 objPos(bullet.getPosition());
      glm::vec2 temp(squadFighters[0].getPosition());
      float distance = glm::length(objPos - temp);
      for(int i = 1; i < squadFighters.size(); i++) {
         temp = squadFighters[i].getPosition();
         if(glm::length(objPos - temp) < distance) {
            distance = glm::length(objPos - temp);
            index = i;
         }
      }
      if(collision(bullet.getBox(), squadFighters[index].getBox())) {
         squadFighters[index].damage();
         return true;
      }
      return false;
   }
}

bool Level::collideWithMissiles(PlayerBullet& bullet) {
   int index = 0;
   if(enemyMissiles.size() > 0) {
      glm::vec2 objPos(bullet.getPosition());
      glm::vec2 temp(enemyMissiles[0].getPosition());
      float distance = glm::length(objPos - temp);
      for(int i = 1; i < enemyMissiles.size(); i++) {
         temp = enemyMissiles[i].getPosition();
         if(glm::length(objPos - temp) < distance) {
            distance = glm::length(objPos - temp);
            index = i;
         }
      }
      if(collision(bullet.getBox(), enemyMissiles[index].getBox())) {
         particles.emplace_back(glm::ivec2(enemyMissiles[index].getPosition().x + 16, enemyMissiles[index].getPosition().y + 16));
         enemyMissiles[index] = enemyMissiles.back();
         score += 1;
         enemyMissiles.pop_back();
         if(sound == true)
            Mix_PlayChannel(-1, RM::SoundCache->createSound("resources/sounds/EnemyDead.wav"), 0);
      }
   }
   return false;
}

bool Level::collideWithSpawners(PlayerBullet& bullet) {
   int index = 0;
   if(spawners.size() > 0) {
      glm::vec2 objPos(bullet.getPosition());
      glm::vec2 temp(spawners[0].getPosition());
      float distance = glm::length(objPos - temp);
      for(int i = 1; i < spawners.size(); i++) {
         temp = spawners[i].getPosition();
         if(glm::length(objPos - temp) < distance) {
            distance = glm::length(objPos - temp);
            index = i;
         }
      }
      if(collision(bullet.getBox(), spawners[index].getBox())) {
         spawners[index].damage();
         score += 1;
         return true;
      }
   }
   return false;
}

bool Level::collision(const glm::ivec4& d1, const glm::ivec4& d2) {
   if(d1.x + d1.z < d2.x)
      return false;
   else if(d1.x > d2.x + d2.z)
      return false;
   else if(d1.y > d2.y + d2.w)
      return false;
   else if(d1.y + d1.w < d2.y)
      return false;
   return true;
}

void Level::restart() {
   healthBase = 10;
   score = 0;
   spawnTimer = 900;
   enemyCrystals.clear();
   squadFighters.clear();
   enemyMissiles.clear();
   playerBullets.clear();
   spawners.clear();
   particles.clear();
}



