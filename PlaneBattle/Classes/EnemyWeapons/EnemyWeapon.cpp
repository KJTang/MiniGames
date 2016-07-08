#include "EnemyWeapon.h"

EnemyWeapon::EnemyWeapon(){}

EnemyWeapon::~EnemyWeapon(){}

EnemyWeapon* EnemyWeapon::create()
{
	auto temp = new EnemyWeapon();
	temp->init();
    temp->autorelease();

	return temp;
}

bool EnemyWeapon::init()
{
	finish = false;

	return true;
}

