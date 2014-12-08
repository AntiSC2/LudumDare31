#ifndef WHITESCREEN_H_INCLUDED
#define WHITESCREEN_H_INCLUDED

class SpriteBatch;

class WhiteScreen {
   public:
      WhiteScreen();
      ~WhiteScreen();
      void update();
      void draw(SpriteBatch* batch);
      void start();
   private:
      int alpha;
      bool started;
};

#endif // WHITESCREEN_H_INCLUDED
