#pragma once

class Camera {
public:
	Camera(float x, float y, float width, float height, int scale = 1);
	~Camera();

	bool intersects(float ox, float oy, float ow, float oh);

	void resize(int width, int height);

	void lookAt(float x, float y);

	int getX();
	int getY();
private:
	float x, y, width, height;
	int scale;
};

