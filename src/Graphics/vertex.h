#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Position {
   GLint x, y;
};

struct Color {
   Color() {
      ;
   }
   Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {
      ;
   }
   GLubyte r, g, b, a;
};

struct Vertex {
   Position position;

   Color color;

   Position UV;

   void setPosition(GLint x, GLint y) {
      position.x = x;
      position.y = y;
   }
   void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
      color.r = r;
      color.g = g;
      color.b = b;
      color.a = a;
   }
   void setUV(GLint x, GLint y) {
      UV.x = x;
      UV.y = y;
   }
};

#endif // VERTEX_H_INCLUDED
