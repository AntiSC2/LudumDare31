#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

class Shader {
   public:
      Shader();
      ~Shader();

      void initProgram(const char* vertPath, const char* fragPath);
      void addAttribute(const char* attributeName);
      void linkProgram();

      GLuint getUniformLocation(const char* uniformName);
      void setCameraMatrix(glm::mat4 cameraMatrix);

      void use();
      void unuse();

   private:
      void compileShader(const char* filePath, GLuint id);

      GLuint numAttributes;
      GLuint programID;
      GLuint vertID, fragID;
};

#endif // SHADER_H_INCLUDED
