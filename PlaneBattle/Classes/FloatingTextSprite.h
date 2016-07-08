#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class FloatingTextSprite : public Layer
{
private:
	Size visibleSize;
	Label *textLabel;
	Action *action;
public:
	FloatingTextSprite();
	~FloatingTextSprite();

	virtual bool init();
	CREATE_FUNC(FloatingTextSprite);
	virtual void update(float dt);

	void start() { if(action) textLabel->runAction(action); this->scheduleUpdate();}
	void remove() { this->removeFromParentAndCleanup(true);}

	void setText(const std::string &str) { textLabel->setString(str);}
	void setTextColor(const Color4B &color) { textLabel->setTextColor(color);}
	void setAction(Action* act) { action = act;}
};
