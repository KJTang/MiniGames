#include "EnemySprite.h"

EnemySprite::EnemySprite(){}

EnemySprite::~EnemySprite(){}

EnemySprite* EnemySprite::create(ArmerSprite* ar, EnemyWeapon* wp)
{
	auto temp = new EnemySprite();
	temp->setArmer(ar);
	temp->setWeapon(wp);
	temp->init();

	return temp;
}

bool EnemySprite::init()
{

	return true;
}

void EnemySprite::update(float dt)
{
	if(weapon->isFinished())
	{
		// when the weapon is finished, it means that the armer was destroyed before
		this->destroy();
	}
}

void EnemySprite::start()
{
	armer->start();
	weapon->enable();

	this->scheduleUpdate();
}

Rect EnemySprite::getArmerRect()
{
	return armer->getArmerRect();
}
