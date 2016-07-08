#include "BulletWeapon.h"
#include "EnemySprite.h"

BulletWeapon::BulletWeapon(){}

BulletWeapon::~BulletWeapon(){}

BulletWeapon* BulletWeapon::create(const std::string &filename)
{
	auto temp = new BulletWeapon();
	temp->setBulletFilename(filename);
	temp->init();
    temp->autorelease();

	return temp;
}

bool BulletWeapon::init()
{
	EnemyWeapon::init();

	visibleSize = Director::getInstance()->getVisibleSize();
	interval = 0.8;
	ArmerPosition = Point(0, 0);

	return true;
}

void BulletWeapon::update(float dt)
{
	for(int i = 0; i != bullets.size(); )
	{
		if(bullets.at(i)->getPositionY() <= 0)
		{
			removeBullet(bullets.at(i));
		}
		else
			i++;
	}

	if(static_cast<EnemySprite*>(this->getParent())->isArmerDestroyed())
	{
		if(bullets.size() == 0)
		{
			this->unscheduleUpdate();
			this->setFinished(true);
			return;
		}
		unschedule(schedule_selector(BulletWeapon::createBullet));
	}
}

void BulletWeapon::enable()
{
	this->runAction(Sequence::create(
//			DelayTime::create(1.0),
			CallFunc::create([&]()
					{
						// create bullets
						schedule(schedule_selector(BulletWeapon::createBullet), interval, kRepeatForever, 0.0);
						this->scheduleUpdate();
					}),
			NULL));
}

void BulletWeapon::disable()
{
	unschedule(schedule_selector(BulletWeapon::createBullet));
	this->unscheduleUpdate();
}

void BulletWeapon::createBullet(float dt)
{
	auto bullet = Sprite::create(bulletFilename);
	this->addChild(bullet);

	bullets.pushBack(bullet);

	// EveryTime create Bullet, We need the Armer's Position
	ArmerPosition = static_cast<EnemySprite*>(this->getParent())->getArmerPosition();
	ArmerSize = static_cast<EnemySprite*>(this->getParent())->getArmerSize();

	bullet->setPosition(Point(ArmerPosition.x, ArmerPosition.y - ArmerSize.width/2));
	bullet->runAction(MoveTo::create(getMovingTime(), Point(ArmerPosition.x, 0)));
}

void BulletWeapon::removeBullet(Sprite* p)
{
	p->removeFromParentAndCleanup(true);
	bullets.eraseObject(p);
}

bool BulletWeapon::isHit(Rect rect)
{
	for(int i = 0; i != bullets.size(); )
	{
		if(bullets.at(i)->getBoundingBox().intersectsRect(rect))
		{
			removeBullet(bullets.at(i));
			return true;
		}
		else
			i++;
	}

	return false;
}
