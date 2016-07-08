#include "PlayerSprite.h"

#include "PlayerWeapons/OneBullet.h"
#include "PlayerWeapons/DoubleBullet.h"

PlayerSprite::PlayerSprite(){}

PlayerSprite::~PlayerSprite(){}

bool PlayerSprite::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();

    planeDestroyed = false;

    plane = Sprite::create("plane/mplane.png");
	this->addChild(plane);
	plane->setScale(visibleSize.width / plane->getContentSize().width / 5);
	auto planeSize = plane->getContentSize();
	plane->setPosition(Point(visibleSize.width / 2, visibleSize.height / 7));

	return true;
}

void PlayerSprite::onEnter()
{
	Node::onEnter();

	auto weapon = OneBullet::create("bullet.png");
	weapon->enable();
	weapons.pushBack(weapon);
	this->addChild(weapon);

	this->scheduleUpdate();
}

void PlayerSprite::update(float dt)
{
	 for(int i = 0; i != weapons.size();)
	 {
		 if(weapons.at(i)->isFinished())
		 {
			 weapons.at(i)->removeFromParentAndCleanup(true);
			 weapons.erase(i);
		 }
		 else
			 i++;
	 }
}

Rect PlayerSprite::getPlaneRect()
{
	Rect newRect;
	Rect pRect = plane->getBoundingBox();
	float scaleRateX = 0.9;
	float scaleRateY = 0.5;
	// 屏幕分辨率
//	if(visibleSize.width < 1080)
//	{
//		scaleRateX = 1.1;
//		scaleRateY = 0.5;
//	}
//	else
//	{
//		scaleRateX = 1.5;
//		scaleRateY = 0.8;
//	}

	newRect.setRect(
			pRect.getMidX() - pRect.size.width/2 * scaleRateX,
			pRect.getMidY() - pRect.size.height/2 * scaleRateY,
			pRect.size.width * scaleRateX,
			pRect.size.height * scaleRateY
	);

	return newRect;
}

void PlayerSprite::DestroyPlane()
{
	plane->setVisible(false);
	for(Vector<PlayerWeapon*>::iterator it = weapons.begin(); it != weapons.end(); it++)
	{
		(*it)->disable();
	}
}

void PlayerSprite::changeWeapon(PlayerWeapon* wp)
{
	 for(Vector<PlayerWeapon*>::iterator it = weapons.begin(); it != weapons.end(); it++)
	 {
		 (*it)->disable();
	 }
	 wp->enable();
	 weapons.pushBack(wp);
	 this->addChild(wp);
}

bool PlayerSprite::isWeaponHit(Rect rect)
{
	for(int i = 0; i != weapons.size(); i++)
	{
		if(weapons.at(i)->isHit(rect))
			return true;
	}
	return false;
}
