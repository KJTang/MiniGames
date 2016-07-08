#pragma once

#include <string>

#include "cocos2d.h"

using namespace cocos2d;

class ArmerSprite : public Sprite
{
private:
	Size visibleSize;
	int Life;
	int Score;

	bool destroyed;
protected:
	Action* action;
	Point startPoint;
public:
	ArmerSprite();
	~ArmerSprite();

	static ArmerSprite* create(const std::string &filename);
	virtual bool init();
	virtual void update();

	void setStartPoint(Point p);
	void start() { this->runAction(action); this->scheduleUpdate();}
	void stop() { this->stopAction(action);}

	void setLife(int l) {Life = l;}
	void setScore(int s) {Score = s;}
	virtual void setAction();
	bool isActionDone() { return action->isDone();}

	int getLife() const { return Life;}
	int getScore() const { return Score;}
	virtual Rect getArmerRect() { return this->getBoundingBox();}

	bool isDestroyed() { return destroyed;}
	void setDestroyed(bool b) { this->setVisible(!b); destroyed = b;}
};

