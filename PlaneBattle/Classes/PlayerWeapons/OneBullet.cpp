#include "OneBullet.h"
#include "PlayerSprite.h"
#include "GameScene.h"

OneBullet::OneBullet(){}

OneBullet::~OneBullet(){}

OneBullet* OneBullet::create(const std::string &filename)
{
	auto temp = new OneBullet();
	temp->setBulletFilename(filename);
	temp->init();

	return temp;
}

bool OneBullet::init()
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

void OneBullet::update(float dt)
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

	if(destroying)
	{
		if(bullets.size() == 0)
		{
			this->unscheduleUpdate();
			this->setFinished(true);
			return;
		}
		unschedule(schedule_selector(OneBullet::createBullet));
	}
}

void OneBullet::enable()
{
	this->runAction(Sequence::create(
			CallFunc::create([&]()
					{
						// create bullets
						schedule(schedule_selector(OneBullet::createBullet), interval, kRepeatForever, 0.0);
						this->scheduleUpdate();
					}),
			NULL));
}

void OneBullet::disable()
{
	unschedule(schedule_selector(OneBullet::createBullet));
	destroying = true;
}

void OneBullet::createBullet(float dt)
{
//	auto bullet = Sprite::create(bulletFilename);
//	this->addChild(bullet);
	auto bullet = Sprite::createWithTexture(bulletBacthNode->getTexture());
	bulletBacthNode->addChild(bullet);

	bullets.pushBack(bullet);

	// EveryTime create Bullet, We need the Player's Position
	PlayerPosition = static_cast<PlayerSprite*>(this->getParent())->getPlanePosition();
	PlayerSize = static_cast<PlayerSprite*>(this->getParent())->getPlaneSize();

	bullet->setScale(visibleSize.width / bullet->getContentSize().width / 35);
	bullet->setPosition(Point(PlayerPosition.x, PlayerPosition.y + PlayerSize.width));
	bullet->runAction(MoveTo::create(getMovingTime(), Point(PlayerPosition.x, visibleSize.height)));
}

void OneBullet::removeBullet(Sprite* p)
{
	p->removeFromParentAndCleanup(true);
	bullets.eraseObject(p);
}

bool OneBullet::isHit(Rect rect)
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
