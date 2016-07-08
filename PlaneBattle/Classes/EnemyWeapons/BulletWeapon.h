#pragma once

#include <string>

#include "cocos2d.h"
#include "EnemyWeapon.h"

using namespace cocos2d;

class BulletWeapon : public EnemyWeapon
{
private:
	Size visibleSize;
	std::string bulletFilename;
	void setBulletFilename(const std::string &filename) { bulletFilename = filename;}
	Vector<Sprite*> bullets;
	float interval; // the interval of send bullets
	Point ArmerPosition;
	Size ArmerSize;

	double getMovingTime() { return ArmerPosition.y / visibleSize.height * 2.5;}
public:
	BulletWeapon();
	~BulletWeapon();

	static BulletWeapon* create(const std::string &filename);
	virtual bool init();
	virtual void update(float dt);

	virtual void enable();
	virtual void disable();

	void createBullet(float dt);
	void removeBullet(Sprite* p);

	virtual bool isHit(Rect rect);
};
