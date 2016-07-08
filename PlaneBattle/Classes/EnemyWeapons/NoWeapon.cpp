#include "NoWeapon.h"
#include "EnemySprite.h"

NoWeapon::NoWeapon(){}

NoWeapon::~NoWeapon(){}

NoWeapon* NoWeapon::create()
{
	auto temp = new NoWeapon();
	temp->init();
    temp->autorelease();

	return temp;
}

bool NoWeapon::init()
{
	EnemyWeapon::init();

	return true;
}

void NoWeapon::update(float dt)
{

}

void NoWeapon::enable()
{

}

void NoWeapon::disable()
{

}

bool NoWeapon::isHit(Rect rect)
{
	return false;
}
