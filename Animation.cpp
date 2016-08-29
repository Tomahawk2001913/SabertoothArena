#include "Animation.h"

Animation::Animation(std::vector<Texture*>* frames, float timeBetweenFrames, ANIMATION_TYPE type) {
	this->frames = frames;
	this->timeBetweenFrames = timeBetweenFrames;
	this->type = type;
}


Animation::~Animation() {
	frames->clear();
	delete frames;
}

Texture* Animation::getFrame(float time) {
	int frame = time / timeBetweenFrames;

	switch (type) {
	case FORWARD:
		frame %= frames->size();
		break;
	case BACKWARD:
		
		break;
	case PINGPONG:

		break;
	default:
		return NULL;
	}

	return (*frames)[frame];
}