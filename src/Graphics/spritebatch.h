#ifndef SPRITEBATCH_H_INCLUDED
#define SPRITEBATCH_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <algorithm>
#include "Vertex.h"

class Glyph {
   public:
      Glyph() {
         ;
      }
      Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color) {
         this->depth = depth;
         this->texture = texture;

         this->bottomLeft.setPosition(destRect.x, destRect.y);
         this->bottomLeft.setUV(uvRect.x, uvRect.y);
         this->bottomLeft.setColor(color.r, color.g, color.b, color.a);

         this->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
         this->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
         this->bottomRight.setColor(color.r, color.g, color.b, color.a);

         this->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
         this->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
         this->topLeft.setColor(color.r, color.g, color.b, color.a);

         this->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
         this->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
         this->topRight.setColor(color.r, color.g, color.b, color.a);
      }

      GLuint texture;
      float depth;

      Vertex topLeft;
      Vertex topRight;
      Vertex bottomLeft;
      Vertex bottomRight;
};

enum class GlyphSortType {
   NONE,
   FRONT_TO_BACK,
   BACK_TO_FRONT,
   TEXTURE
};

class RenderBatch {
   public:
      RenderBatch(GLuint offSet, GLuint numvertices, GLuint teXture) : offset(offSet), numVertices(numvertices), texture(teXture) {
         ;
      }
      GLuint offset;
      GLuint numVertices;
      GLuint texture;
};

class SpriteBatch {
   public:
      SpriteBatch();
      ~SpriteBatch();

      void init();
      void begin(GlyphSortType sortingType = GlyphSortType::TEXTURE);
      void end();
      void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color);
      void renderDraw();

   private:
      void sortGlyphs();
      void createRenderBatches();

      static bool compareFrontToBack(Glyph* a, Glyph* b);
      static bool compareBackToFront(Glyph* a, Glyph* b);
      static bool compareTexture(Glyph* a, Glyph* b);

      GlyphSortType sortType;

      std::vector<Glyph*> GlyphsPointers;
      std::vector<Glyph> Glyphs;
      std::vector<RenderBatch> RenderBatches;

      GLuint vboID;
      GLuint vaoID;
};


#endif // SPRITEBATCH_H_INCLUDED
