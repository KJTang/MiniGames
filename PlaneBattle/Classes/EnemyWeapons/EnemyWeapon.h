#pragma once

#include "cocos2d.h"

class EnemySprite;

using namespace cocos2d;

class EnemyWeapon : public Node
{
private:
	bool finish;
protected:

public:
	EnemyWeapon();
	~EnemyWeapon();

	static EnemyWeapon* create();
	virtual bool init();

	virtual void enable() {}
	virtual void disable() {}

	virtual bool isHit(Rect rect) { return false;}

	bool isFinished() { return finish;}
	void setFinished(bool b) { finish = b;}
};
