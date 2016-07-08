#pragma once

#include "cocos2d.h"

using namespace cocos2d;

struct myEnemy
{
	float interval;
	Point start;
	int type;
};

class GameBarrier
{
private:
	GameBarrier();
public:
	static std::vector<myEnemy> getEnemys(int gamelevel);
};
