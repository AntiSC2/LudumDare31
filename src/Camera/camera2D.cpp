#include "camera2D.h"

Camera2D::Camera2D(int w, int h) : width(w), height(h), scale(1.0f), needUpdate(0), position(0, 0), cameraMatrix(1), orthoMatrix(1) {
   ;
}

Camera2D::~Camera2D() {
   ;
}

void Camera2D::init(int w, int h) {
   width = w;
   height = h;

   orthoMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
   needUpdate = 1;
}

void Camera2D::update() {
   if(needUpdate) {
      glm::vec3 translate(-position.x + width / 2, -position.y + height / 2, 0.0f);
      cameraMatrix = glm::translate(orthoMatrix, translate);

      glm::vec3 Scale(scale, -scale, 0.0f);
      cameraMatrix = glm::scale(glm::mat4(1.0f), Scale) * cameraMatrix;
      needUpdate = false;
   }
}

void Camera2D::setPosition(glm::vec2 position) {
   this->position = position;
   needUpdate = true;
}

void Camera2D::setScale(GLfloat scale) {
   this->scale = scale;
   needUpdate = true;
}

bool Camera2D::cameraCulling(const glm::vec4& destRect) {
   glm::vec4 cameraHitBox(position.x - (width / 2), position.y -(height / 2), width, height);
   if(destRect.x > cameraHitBox.x + cameraHitBox.z)
      return true;
   else if(destRect.x + destRect.z < cameraHitBox.x)
      return true;
   else if(destRect.y + destRect.w < cameraHitBox.y)
      return true;
   else if(destRect.y > cameraHitBox.y + cameraHitBox.w)
      return true;
   return false;
}

glm::vec2 Camera2D::getPosition() {
   return position;
}

GLfloat Camera2D::getScale() {
   return scale;
}

glm::mat4 Camera2D::getCameraMatrix() {
   return cameraMatrix;
}

int Camera2D::getWidth() {
   return width;
}

int Camera2D::getHeight() {
   return height;
}
