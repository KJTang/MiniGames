#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(){}

PlayerWeapon::~PlayerWeapon(){}

PlayerWeapon* PlayerWeapon::create()
{
	auto temp = new PlayerWeapon();
	temp->init();

	return temp;
}

bool PlayerWeapon::init()
{
	finish = false;

	return true;
}

