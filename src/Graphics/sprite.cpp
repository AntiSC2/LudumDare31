#include "sprite.h"

Sprite::Sprite() : tex(nullptr) {
   ;
}

Sprite::~Sprite() {
   tex = nullptr;
}

void Sprite::initSprite(GLint xv, GLint yv, GLint width, GLint height, GLubyte r, GLubyte g, GLubyte b, GLubyte a, const char* filePath) {

   tex = RM::TextureCache->createTexture(filePath);

   destRect.x = xv;
   destRect.y = yv;
   destRect.z = width;
   destRect.w = height;

   uvRect.x = 0;
   uvRect.y = 0;
   uvRect.z = 1;
   uvRect.w = 1;

   color.r = r;
   color.g = g;
   color.b = b;
   color.a = a;
}

void Sprite::render(SpriteBatch* batch) {
   batch->draw(destRect, uvRect, tex->getID(), 0, color);
}

void Sprite::updatePosition(int x, int y) {
   destRect.x = x;
   destRect.y = y;
}
