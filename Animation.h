#pragma once

#include <vector>
#include "Texture.h"

class Animation {
public:
	enum ANIMATION_TYPE {
		FORWARD, BACKWARD, PINGPONG
	};

	Animation(std::vector<Texture*>* frames, float timeBetweenFrames, ANIMATION_TYPE type = FORWARD);
	~Animation();

	Texture* getFrame(float time);
private:
	std::vector<Texture*>* frames;
	float timeBetweenFrames = 0;
	ANIMATION_TYPE type = FORWARD;
};

