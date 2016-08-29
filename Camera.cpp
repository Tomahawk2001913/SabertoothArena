#include "Camera.h"

Camera::Camera(float x, float y, float width, float height, int scale) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->scale = scale;
}

Camera::~Camera() {

}

bool Camera::intersects(float ox, float oy, float ow, float oh) {
	ox *= scale;
	oy *= scale;
	ow *= scale;
	oh *= scale;

	if(ox + ow < x || ox > x + width ||
	   oy + oh < height || oy > y + height) return false;

	return true;
}

void Camera::resize(int width, int height) {
	// Do something here.
}

void Camera::lookAt(float x, float y) {
	this->x = x * scale - width / 2;
	this->y = y * scale - height / 2;
}

int Camera::getX() {
	return x;
}

int Camera::getY() {
	return y;
}