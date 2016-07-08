#include "BossArmer.h"

BossArmer::BossArmer(){}

BossArmer::~BossArmer(){}

BossArmer* BossArmer::create(const std::string& filename)
{
    BossArmer *pRet = new BossArmer();
    if (pRet && pRet->initWithFile(filename) && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = 0;
        return 0;
    }
}

BossArmer* BossArmer::create()
{
    return create("plane/enemy_boss.png");
}

bool BossArmer::init()
{
	ArmerSprite::init();

	visibleSize = Director::getInstance()->getVisibleSize();

	setStartPoint(Point(visibleSize.width/2, visibleSize.height + this->getContentSize().height));
	this->setScale(visibleSize.width/this->getContentSize().width/1.5);

	setLife(1200);
	setScore(50000);
	setAction();

	return true;
}

void BossArmer::onEnter()
{
	ArmerSprite::onEnter();
}

void BossArmer::update(float dt)
{
	// if action has not finished
	if(this->getActionByTag(1) && !this->getActionByTag(1)->isDone())
	{
		return;
	}

	this->unscheduleUpdate();
	this->setDestroyed(true);
}

void BossArmer::setAction()
{
	action = RepeatForever::create(Sequence::create(
//			DelayTime::create(0.5),
			MoveTo::create(1.0, Point(visibleSize.width*0.50, visibleSize.height*0.80)),
			MoveTo::create(1.5, Point(visibleSize.width*0.20, visibleSize.height*0.80)),
			MoveTo::create(1.5, Point(visibleSize.width*0.80, visibleSize.height*0.80)),
			MoveTo::create(1.5, Point(visibleSize.width*0.50, visibleSize.height*0.95)),
			MoveTo::create(1.5, Point(visibleSize.width*0.10, visibleSize.height*0.60)),
			MoveTo::create(1.5, Point(visibleSize.width*0.90, visibleSize.height*0.60)),
			MoveTo::create(1.5, Point(visibleSize.width*0.50, visibleSize.height*0.95)),
			NULL));
	action->setTag(1);
}

Rect BossArmer::getArmerRect()
{
	// TODO: maybe sometime can change the boundingbox, make the boss more powerful
	return this->getBoundingBox();
}
