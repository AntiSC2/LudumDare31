#include "shader.h"

Shader::Shader() : programID(0), numAttributes(0), vertID(0), fragID(0) {

}

Shader::~Shader() {
   if(programID != 0) {
      glDeleteProgram(programID);
   }
}

void Shader::initProgram(const char* vertPath, const char* fragPath) {

   programID = glCreateProgram();
   vertID = glCreateShader(GL_VERTEX_SHADER);
   if(vertID == 0)
   {
      printf("Vertex shader %s failed to be created!\n", vertPath);
   }
   fragID = glCreateShader(GL_FRAGMENT_SHADER);
   if(fragID == 0)
   {
      printf("Fragment shader %s failed to be created!\n", fragPath);
   }

   compileShader(vertPath, vertID);
   compileShader(fragPath, fragID);
}

void Shader::compileShader(const char* filePath, GLuint id) {

   std::ifstream shaderFile(filePath);
   if (shaderFile.fail()) {
      printf("Failed to open %s\n", filePath);
   }

   //File contents stores all the text in the file
   std::string fileContents = "";
   //line is used to grab each line of the file
   std::string line;

   //Get all the lines in the file and add it to the contents
   while (std::getline(shaderFile, line)) {
      fileContents += line + "\n";
   }

   shaderFile.close();

   //get a pointer to our file contents c string;
   const char* contentsPtr = fileContents.c_str();
   //tell opengl that we want to use fileContents as the contents of the shader file
   glShaderSource(id, 1, &contentsPtr, nullptr);

   //compile the shader
   glCompileShader(id);

   //check for errors
   GLint success = 0;
   glGetShaderiv(id, GL_COMPILE_STATUS, &success);

   if (success == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

      //The maxLength includes the NULL character
      std::vector<char> errorLog(maxLength);
      glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

      //Provide the infolog in whatever manor you deem best.
      //Exit with failure.
      glDeleteShader(id); //Don't leak the shader.

      //Print error log and quit
      printf("%s\n", &(errorLog[0]));
      printf("Shader failed %s to compile \n", filePath);
   }
}


void Shader::addAttribute(const char* attributeName) {
   glBindAttribLocation(programID, numAttributes++, attributeName);
}

void Shader::linkProgram() {

   glAttachShader(programID, vertID);
   glAttachShader(programID, fragID);

   glLinkProgram(programID);

   GLint isLinked = 0;
   glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

   if (isLinked == GL_FALSE) {
      GLint maxLength = 0;
      glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

      //The maxLength includes the NULL character
      std::vector<char> errorLog(maxLength);
      glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);



      //We don't need the program anymore.
      glDeleteProgram(programID);
      //Don't leak shaders either.
      glDeleteShader(vertID);
      glDeleteShader(fragID);

      //print the error log and quit
      printf("%s\n", &(errorLog[0]));
      printf("Shaders failed to link!\n");
   }

   //Always detach shaders after a successful link.
   glDetachShader(programID, vertID);
   glDetachShader(programID, fragID);
   glDeleteShader(vertID);
   glDeleteShader(fragID);
}

GLuint Shader::getUniformLocation(const char* uniformName) {
   GLuint location = glGetUniformLocation(programID, uniformName);
   if(location == GL_INVALID_INDEX) {
      //printf("Uniform %s was not found in shader!", uniformName);
   }
   return location;
}

void Shader::setCameraMatrix(glm::mat4 cameraMatrix) {
   GLuint location = getUniformLocation("Projection");
   glUniformMatrix4fv(location, 1, GL_FALSE, &(cameraMatrix[0][0]));
}

void Shader::use() {
   glUseProgram(programID);

   for (GLuint i = 0; i < numAttributes; i++) {
      glEnableVertexAttribArray(i);
   }
}

void Shader::unuse() {
   glUseProgram(0);
   for (GLuint i = 0; i < numAttributes; i++) {
      glDisableVertexAttribArray(i);
   }
}

