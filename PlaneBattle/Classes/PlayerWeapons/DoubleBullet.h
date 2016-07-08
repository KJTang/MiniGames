#pragma once

#include <string>

#include "cocos2d.h"
#include "PlayerWeapons/PlayerWeapon.h"

using namespace cocos2d;

class DoubleBullet : public PlayerWeapon
{
private:
	Size visibleSize;
	std::string bulletFilename;
	void setBulletFilename(const std::string &filename) { bulletFilename = filename;}

	Vector<Sprite*> bullets;
	SpriteBatchNode *bulletBacthNode;

	float interval; // the interval of send bullets
	Point PlayerPosition;
	Size PlayerSize;
	double getMovingTime() { return (visibleSize.height - PlayerPosition.y) / visibleSize.height * 2.5;}
	bool destroying;
public:
	DoubleBullet();
	~DoubleBullet();

	static DoubleBullet* create(const std::string &filename);
	virtual bool init();
	virtual void update(float dt);

	virtual void enable();
	virtual void disable();

	void createBullet(float dt);
	void removeBullet(Sprite* p);

	virtual bool isHit(Rect rect);
};
