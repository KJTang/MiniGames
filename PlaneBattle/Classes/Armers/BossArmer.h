#pragma once

#include "cocos2d.h"
#include "ArmerSprite.h"

using namespace cocos2d;

class BossArmer : public ArmerSprite
{
private:
	Size visibleSize;
public:
	BossArmer();
	~BossArmer();

	static BossArmer* create(const std::string& filename);
	static BossArmer* create();
	bool init();
	void onEnter();
	void update(float dt);

	void setAction();
	virtual Rect getArmerRect();
};
