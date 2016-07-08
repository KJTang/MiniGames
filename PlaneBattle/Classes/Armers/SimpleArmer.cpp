#include "SimpleArmer.h"

SimpleArmer::SimpleArmer(){}

SimpleArmer::~SimpleArmer(){}

SimpleArmer* SimpleArmer::create(const std::string& filename)
{
    SimpleArmer *pRet = new SimpleArmer();
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

bool SimpleArmer::init()
{
	ArmerSprite::init();

	visibleSize = Director::getInstance()->getVisibleSize();

	setStartPoint(Point(visibleSize.width/2, visibleSize.height + this->getContentSize().height/2));
	this->setScale(visibleSize.width/this->getContentSize().width/5);

	setLife(5);
	setScore(800);
	setAction();

	return true;
}

void SimpleArmer::onEnter()
{
	ArmerSprite::onEnter();
}

void SimpleArmer::update(float dt)
{
	// if action has not finished
	if(this->getActionByTag(1) && !this->getActionByTag(1)->isDone())
	{
		return;
	}

	this->unscheduleUpdate();
	this->setDestroyed(true);
}

void SimpleArmer::setAction()
{
	action = Sequence::create(
//			DelayTime::create(0.5),
			MoveTo::create(2.0, Point(startPoint.x, 0)),
			NULL);
	action->setTag(1);
}
