#pragma once

#include <string>

#include "cocos2d.h"
#include "EnemyWeapon.h"

using namespace cocos2d;

class NoWeapon : public EnemyWeapon
{
private:
public:
	NoWeapon();
	~NoWeapon();

	static NoWeapon* create();
	virtual bool init();
	virtual void update(float dt);

	virtual void enable();
	virtual void disable();

	virtual bool isHit(Rect rect);
};
