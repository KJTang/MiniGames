#include "DoubleBullet.h"
#include "PlayerSprite.h"
#include "GameScene.h"

DoubleBullet::DoubleBullet(){}

DoubleBullet::~DoubleBullet(){}

DoubleBullet* DoubleBullet::create(const std::string &filename)
{
	auto temp = new DoubleBullet();
	temp->setBulletFilename(filename);
	temp->init();

	return temp;
}

bool DoubleBullet::init()
{
	PlayerWeapon::init();

	destroying = false;
	visibleSize = Director::getInstance()->getVisibleSize();
	interval = 0.07;
	PlayerPosition = Point(0, 0);

	bulletBacthNode = SpriteBatchNode::create(bulletFilename);
	this->addChild(bulletBacthNode);

	return true;
}

void DoubleBullet::update(float dt)
{
	for(int i = 0; i != bullets.size(); )
	{
		if(bullets.at(i)->getPositionY() >= visibleSize.height)
		{
			removeBullet(bullets.at(i));
		}
		else
			i++;
	}

//	if(static_cast<PlayerSprite*>(this->getParent())->isPlaneDestroyed())
	if(destroying)
	{
		if(bullets.size() == 0)
		{
			this->unscheduleUpdate();
			this->setFinished(true);
			return;
		}
		unschedule(schedule_selector(DoubleBullet::createBullet));
	}
}

void DoubleBullet::enable()
{
	this->runAction(Sequence::create(
			CallFunc::create([&]()
					{
						// create bullets
						schedule(schedule_selector(DoubleBullet::createBullet), interval, kRepeatForever, 0.0);
						this->scheduleUpdate();
					}),
			NULL));
}

void DoubleBullet::disable()
{
	unschedule(schedule_selector(DoubleBullet::createBullet));
	destroying = true;
}

void DoubleBullet::createBullet(float dt)
{
//	auto bullet = Sprite::create(bulletFilename);
//	this->addChild(bullet);
//	auto bullet2 = Sprite::create(bulletFilename);
//	this->addChild(bullet2);

	auto bullet = Sprite::createWithTexture(bulletBacthNode->getTexture());
	bulletBacthNode->addChild(bullet);
	auto bullet2 = Sprite::createWithTexture(bulletBacthNode->getTexture());
	bulletBacthNode->addChild(bullet2);

	bullets.pushBack(bullet);
	bullets.pushBack(bullet2);

	// EveryTime create Bullet, We need the Player's Position
	PlayerPosition = static_cast<PlayerSprite*>(this->getParent())->getPlanePosition();
	PlayerSize = static_cast<PlayerSprite*>(this->getParent())->getPlaneSize();

	bullet->setScale(visibleSize.width / bullet->getContentSize().width / 35);
	bullet->setPosition(Point(PlayerPosition.x - PlayerSize.width/2, PlayerPosition.y + PlayerSize.height/2));
	bullet->runAction(MoveTo::create(getMovingTime(), Point(bullet->getPositionX(), visibleSize.height)));
	bullet2->setScale(visibleSize.width / bullet2->getContentSize().width / 35);
	bullet2->setPosition(Point(PlayerPosition.x + PlayerSize.width/2, PlayerPosition.y + PlayerSize.height/2));
	bullet2->runAction(MoveTo::create(getMovingTime(), Point(bullet2->getPositionX(), visibleSize.height)));
}

void DoubleBullet::removeBullet(Sprite* p)
{
	p->removeFromParentAndCleanup(true);
	bullets.eraseObject(p);
}

bool DoubleBullet::isHit(Rect rect)
{
	for(int i = 0; i != bullets.size(); )
	{
		if(bullets.at(i)->getBoundingBox().intersectsRect(rect))
		{
			GameScene::getInstance()->getGameLayer()->playAnimation(bullets.at(i)->getPosition());
			removeBullet(bullets.at(i));
			return true;
		}
		else
			i++;
	}

	return false;
}
