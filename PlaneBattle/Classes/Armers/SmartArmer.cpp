#include "SmartArmer.h"

SmartArmer::SmartArmer(){}

SmartArmer::~SmartArmer(){}

SmartArmer* SmartArmer::create(const std::string& filename)
{
    SmartArmer *pRet = new SmartArmer();
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

bool SmartArmer::init()
{
	ArmerSprite::init();

	visibleSize = Director::getInstance()->getVisibleSize();

	setStartPoint(Point(visibleSize.width/4, visibleSize.height + this->getContentSize().height/2));
	this->setScale(visibleSize.width/this->getContentSize().width/5);

	setLife(10);
	setScore(2000);
	setAction();

	return true;
}

void SmartArmer::onEnter()
{
	ArmerSprite::onEnter();
}

void SmartArmer::update(float dt)
{
	// if action has not finished
	if(this->getActionByTag(1) && !this->getActionByTag(1)->isDone())
	{
		return;
	}

	this->unscheduleUpdate();
	this->setDestroyed(true);
}

void SmartArmer::setAction()
{
	action = Sequence::create(
			MoveTo::create(1.2, Point(startPoint.x, visibleSize.height*0.65)),
			DelayTime::create(0.1),
			MoveTo::create(2.5, Point(visibleSize.width-startPoint.x, 0)),
			NULL);
	action->setTag(1);
}
