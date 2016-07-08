#pragma once

#include "cocos2d.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace cocos2d;

class RectMovingSprite : public Sprite
{
private:
	enum
	{
		up,down,left,right
	};
	int position;

	Size visibleSize;
	Point startPoint, nextPoint;
	float slope;
	// time to delay before start
	float delay;
	// run through visibleSize.width need how much time
	float speed;
	float getMovingTime();

	Point getNextPoint();
public:
	RectMovingSprite();
	~RectMovingSprite();

	static RectMovingSprite* create(const std::string& filename);
	bool init();
	void update(float dt);
	bool start();

	void setRandSeed() {srand(time(NULL));}; // only use once is enough
	void setDelayTime(float d) {delay = d;};
	void setSpeed(float sp) {speed = sp;};
};
