#pragma once

#include <string>

#include "cocos2d.h"
#include "EnemyWeapon.h"

using namespace cocos2d;

class BossWeapon : public EnemyWeapon
{
private:
	Size visibleSize;
	std::string bulletFilename;
	void setBulletFilename(const std::string &filename) { bulletFilename = filename;}

	Vector<Sprite*> bullets;
	SpriteBatchNode *bulletBacthNode;

	float interval; // the interval of send bullets
	Point ArmerPosition;
	Size ArmerSize;

	double getMovingTime() { return ArmerPosition.y / visibleSize.height * 1.8;}
public:
	BossWeapon();
	~BossWeapon();

	static BossWeapon* create(const std::string &filename);
	static BossWeapon* create();
	virtual bool init();
	virtual void update(float dt);

	virtual void enable();
	virtual void disable();

	void createBullet(float dt);
	void removeBullet(Sprite* p);

	virtual bool isHit(Rect rect);
};
