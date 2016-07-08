#include "BossWeapon.h"
#include "EnemySprite.h"

BossWeapon::BossWeapon(){}

BossWeapon::~BossWeapon(){}

BossWeapon* BossWeapon::create(const std::string &filename)
{
	auto temp = new BossWeapon();
	temp->setBulletFilename(filename);
	temp->init();
    temp->autorelease();

	return temp;
}

BossWeapon* BossWeapon::create()
{
	return create("bullet_2.png");
}

bool BossWeapon::init()
{
	EnemyWeapon::init();

	visibleSize = Director::getInstance()->getVisibleSize();
	interval = 0.55;
	ArmerPosition = Point(0, 0);

	bulletBacthNode = SpriteBatchNode::create(bulletFilename);
	this->addChild(bulletBacthNode);

	return true;
}

void BossWeapon::update(float dt)
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
		unschedule(schedule_selector(BossWeapon::createBullet));
	}
}

void BossWeapon::enable()
{
	this->runAction(Sequence::create(
//			DelayTime::create(1.0),
			CallFunc::create([&]()
					{
						// create bullets
						schedule(schedule_selector(BossWeapon::createBullet), interval, kRepeatForever, 0.0);
						this->scheduleUpdate();
					}),
			NULL));
}

void BossWeapon::disable()
{
	unschedule(schedule_selector(BossWeapon::createBullet));
	this->unscheduleUpdate();
}

void BossWeapon::createBullet(float dt)
{
	auto bullet1 = Sprite::createWithTexture(bulletBacthNode->getTexture());
	bulletBacthNode->addChild(bullet1);
	auto bullet2 = Sprite::createWithTexture(bulletBacthNode->getTexture());
	bulletBacthNode->addChild(bullet2);
	auto bullet3 = Sprite::createWithTexture(bulletBacthNode->getTexture());
	bulletBacthNode->addChild(bullet3);
	auto bullet4 = Sprite::createWithTexture(bulletBacthNode->getTexture());
	bulletBacthNode->addChild(bullet4);

	bullets.pushBack(bullet1);
	bullets.pushBack(bullet2);
	bullets.pushBack(bullet3);
	bullets.pushBack(bullet4);

	ArmerPosition = static_cast<EnemySprite*>(this->getParent())->getArmerPosition();
	ArmerSize = static_cast<EnemySprite*>(this->getParent())->getArmerSize();

	bullet1->setPosition(Point(ArmerPosition.x-ArmerSize.width/2, ArmerPosition.y-ArmerSize.height/2));
	bullet1->runAction(MoveTo::create(getMovingTime(), Point(ArmerPosition.x-ArmerSize.width/2, 0)));

	bullet2->setPosition(Point(ArmerPosition.x+ArmerSize.width/2, ArmerPosition.y-ArmerSize.height/2));
	bullet2->runAction(MoveTo::create(getMovingTime(), Point(ArmerPosition.x+ArmerSize.width/2, 0)));

	bullet3->setPosition(Point(ArmerPosition.x-ArmerSize.width/4, ArmerPosition.y-ArmerSize.height/2));
	bullet3->runAction(MoveTo::create(getMovingTime(), Point(ArmerPosition.x-ArmerSize.width/4, 0)));

	bullet4->setPosition(Point(ArmerPosition.x+ArmerSize.width/4, ArmerPosition.y-ArmerSize.height/2));
	bullet4->runAction(MoveTo::create(getMovingTime(), Point(ArmerPosition.x+ArmerSize.width/4, 0)));
}

void BossWeapon::removeBullet(Sprite* p)
{
	p->removeFromParentAndCleanup(true);
	bullets.eraseObject(p);
}

bool BossWeapon::isHit(Rect rect)
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
