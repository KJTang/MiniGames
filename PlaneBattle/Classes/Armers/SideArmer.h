#pragma once

#include "cocos2d.h"
#include "ArmerSprite.h"

using namespace cocos2d;

class SideArmer : public ArmerSprite
{
private:
	Size visibleSize;
public:
	SideArmer();
	~SideArmer();

	static SideArmer* create(const std::string& filename);
	bool init();
	void onEnter();
	void update(float dt);

	void setAction();
};
