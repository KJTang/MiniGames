#pragma once

#include "cocos2d.h"

#include "Armers/ArmerSprite.h"
#include "EnemyWeapons/EnemyWeapon.h"

using namespace cocos2d;

class EnemySprite : public Node
{
private:
	ArmerSprite *armer;
	EnemyWeapon *weapon;
	void setArmer(ArmerSprite* ar) { armer = ar; this->addChild(armer);}
	void setWeapon(EnemyWeapon* wp) { weapon = wp; this->addChild(weapon);}
protected:

public:
	EnemySprite();
	~EnemySprite();

	virtual bool init();
	static EnemySprite* create(ArmerSprite* ar, EnemyWeapon* wp);
	virtual void update(float dt);
	virtual void start();
	virtual void destroy() { this->removeFromParentAndCleanup(true);}

	void setArmerPosition(Point p) {armer->setStartPoint(p);}
	Point getArmerPosition() { return armer->getPosition();}
	Size getArmerSize() { return armer->getContentSize();}
	Rect getArmerRect();
	void setArmerLife(int lf) { armer->setLife(lf);}
	int getArmerLife() { return armer->getLife();}
	int getArmerScore() { return armer->getScore();}
	void destroyArmer() { armer->setDestroyed(true);}
	bool isArmerDestroyed() { return armer->isDestroyed();}

	EnemyWeapon* getWeapon() const { return weapon;}
};
