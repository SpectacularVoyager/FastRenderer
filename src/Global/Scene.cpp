#include "Scene.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_projection.hpp>


void Scene::onResize(int width, int height){
	this->width=width;
	this->height=height;
	camera.setAspect((float)width/float(height));
}

void Camera::setFOV(float deg){
	this->fov=deg;
	recompute();
}
void Camera::setAspect(float aspect){
	this->aspect=aspect;
	recompute();
}
void Camera::setNear(float near){
	this->near=near;
	recompute();
}
void Camera::setFar(float far){
	this->far=far;
	recompute();
}
