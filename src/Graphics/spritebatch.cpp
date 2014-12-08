#include "spritebatch.h"

SpriteBatch::SpriteBatch() : vboID(0), vaoID(0) {
   ;
}

SpriteBatch::~SpriteBatch() {
   if(vaoID != 0) {
      glDeleteVertexArrays(1, &vaoID);
   }
   if(vboID != 0) {
      glDeleteBuffers(1, &vboID);
   }
}

void SpriteBatch::init() {
   if(vaoID == 0) {
      glGenVertexArrays(1, &vaoID);
   }
   glBindVertexArray(vaoID);
   if(vboID == 0) {
      glGenBuffers(1, &vboID);
   }
   glBindBuffer(GL_ARRAY_BUFFER, vboID);

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);

   glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
   glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
   glVertexAttribPointer(2, 2, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

   glBindVertexArray(0);
}

void SpriteBatch::begin(GlyphSortType sortingType) {
   sortType = sortingType;
   RenderBatches.clear();
   Glyphs.clear();
}

void SpriteBatch::end() {
   GlyphsPointers.resize(Glyphs.size());
   for(int i = 0; i < Glyphs.size(); i++) {
      GlyphsPointers[i] = &Glyphs[i];
   }
   sortGlyphs();
   createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color& color) {
   Glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::renderDraw() {

   glBindVertexArray(vaoID);

   for(int i = 0; i < RenderBatches.size(); i++) {
      glBindTexture(GL_TEXTURE_2D, RenderBatches[i].texture);
      glDrawArrays(GL_TRIANGLES, RenderBatches[i].offset, RenderBatches[i].numVertices);
   }
}

void SpriteBatch::sortGlyphs() {
   switch(sortType) {
      case GlyphSortType::BACK_TO_FRONT :
         std::stable_sort(GlyphsPointers.begin(), GlyphsPointers.end(), compareBackToFront);
         break;
      case GlyphSortType::FRONT_TO_BACK :
         std::stable_sort(GlyphsPointers.begin(), GlyphsPointers.end(), compareFrontToBack);
         break;
      case GlyphSortType::TEXTURE :
         std::stable_sort(GlyphsPointers.begin(), GlyphsPointers.end(), compareTexture);
         break;
   }
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
   return a->depth < b->depth;
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
   return a->depth > b->depth;
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
   return a->texture < b->texture;
}

void SpriteBatch::createRenderBatches() {
   if(GlyphsPointers.empty()) {
      return;
   }
   std::vector<Vertex> vertices;
   vertices.resize(GlyphsPointers.size() * 6);
   int offset = 0;
   int cv = 0;

   //Add the first batch
   RenderBatches.emplace_back(offset, 6, GlyphsPointers[0]->texture);
   vertices[cv++] = GlyphsPointers[0]->topLeft;
   vertices[cv++] = GlyphsPointers[0]->bottomLeft;
   vertices[cv++] = GlyphsPointers[0]->bottomRight;
   vertices[cv++] = GlyphsPointers[0]->bottomRight;
   vertices[cv++] = GlyphsPointers[0]->topRight;
   vertices[cv++] = GlyphsPointers[0]->topLeft;
   offset += 6;

   //Add all the rest of the GlyphsPointers
   for (int cg = 1; cg < GlyphsPointers.size(); cg++) {

      // Check if this glyph can be part of the current batch
      if (GlyphsPointers[cg]->texture != GlyphsPointers[cg - 1]->texture) {
         // Make a new batch
         RenderBatches.emplace_back(offset, 6, GlyphsPointers[cg]->texture);
      } else {
         // If its part of the current batch, just increase numVertices
         RenderBatches.back().numVertices += 6;
      }
      vertices[cv++] = GlyphsPointers[cg]->topLeft;
      vertices[cv++] = GlyphsPointers[cg]->bottomLeft;
      vertices[cv++] = GlyphsPointers[cg]->bottomRight;
      vertices[cv++] = GlyphsPointers[cg]->bottomRight;
      vertices[cv++] = GlyphsPointers[cg]->topRight;
      vertices[cv++] = GlyphsPointers[cg]->topLeft;
      offset += 6;
   }


   glBindBuffer(GL_ARRAY_BUFFER, vboID);
   glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

   glBindBuffer(GL_ARRAY_BUFFER, 0);

}
