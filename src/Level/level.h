#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include <Graphics/spritebatch.h>
#include <Graphics/sprite.h>
#include <Graphics/spritefont.h>
#include <vector>
#include "Entities/player.h"
#include "Entities/playerbullet.h"
#include "Entities/enemycrystal.h"
#include "Entities/squadfighter.h"
#include "Entities/enemymissile.h"
#include "Entities/whitescreen.h"
#include "Entities/spawner.h"
#include "Entities/partice.h"
class Shield;
class Camera2D;

enum class GAMESTATE {
   MENU, PAUSE, PLAY, GAMEOVER
};

class Level {
   public:
      Level(Camera2D* camera);
      ~Level();
      void init(const char* filePath);
      void update();
      void drawLevel(SpriteBatch* batch);
      void collideWithCrystals(PlayerBullet& bullet);
      bool collideWithSquad(PlayerBullet& bullet);
      bool collideWithMissiles(PlayerBullet& bullet);
      bool collideWithSpawners(PlayerBullet& bullet);
   private:
      bool sound;
      bool music;
      void restart();
      bool shake;
      int shakeTimer;
      WhiteScreen explosion;
      Camera2D* levelCamera;
      SpriteBatch levelBatch;
      Player player;
      std::vector<PlayerBullet> playerBullets;
      std::vector<EnemyCrystal> enemyCrystals;
      std::vector<SquadFighter> squadFighters;
      std::vector<EnemyMissile> enemyMissiles;
      std::vector<Spawner> spawners;
      std::vector<Particle> particles;
      bool collision(const glm::ivec4& d1, const glm::ivec4& d2);
      int timerCrystal;
      int timerSquadFighter;
      Shield* shield;
      int score;
      int showScore;
      int healthBase;
      int spawnTimer;
      bool once;
      GAMESTATE gameState;
};

#endif // LEVEL_H_INCLUDED
