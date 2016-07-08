#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class PlayerWeapon : public Node
{
private:
	bool finish;
protected:

public:
	PlayerWeapon();
	~PlayerWeapon();

	static PlayerWeapon* create();
	virtual bool init();

	virtual void enable() {}
	virtual void disable() {}

	virtual bool isHit(Rect rect) { return false;}

	bool isFinished() { return finish;}
	void setFinished(bool b) { finish = b;}
};
