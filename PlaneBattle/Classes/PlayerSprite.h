#pragma once

#include "cocos2d.h"
#include "PlayerWeapons/PlayerWeapon.h"

using namespace cocos2d;

class PlayerSprite : public Node
{
private:
	Size visibleSize;
	Sprite *plane;
	bool planeDestroyed;
	Vector<PlayerWeapon*> weapons;
public:
	PlayerSprite();
	~PlayerSprite();
	virtual bool init();
	virtual void onEnter();
	virtual void update(float dt);
	CREATE_FUNC(PlayerSprite);

	bool isPlaneDestroyed() const { return planeDestroyed;}
	Rect getPlaneRect();
	const Size getPlaneSize() { return plane->getContentSize();}
	const Point getPlanePosition() { return plane->getPosition();}
	void setPlanePosition(Point p) { plane->setPosition(p);}
	void DestroyPlane();

	void changeWeapon(PlayerWeapon *wp);
	bool isWeaponHit(Rect rect);
};
