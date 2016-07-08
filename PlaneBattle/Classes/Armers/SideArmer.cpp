#include "SideArmer.h"

SideArmer::SideArmer(){}

SideArmer::~SideArmer(){}

SideArmer* SideArmer::create(const std::string& filename)
{
    SideArmer *pRet = new SideArmer();
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

bool SideArmer::init()
{
	ArmerSprite::init();

	visibleSize = Director::getInstance()->getVisibleSize();

	setStartPoint(Point(0, visibleSize.height*0.8));
	this->setScale(visibleSize.width/this->getContentSize().width/5);

	setLife(12);
	setScore(4500);
	setAction();

	return true;
}

void SideArmer::onEnter()
{
	ArmerSprite::onEnter();
}

void SideArmer::update(float dt)
{
	// if action has not finished
	if(this->getActionByTag(1) && !this->getActionByTag(1)->isDone())
	{
		return;
	}

	this->unscheduleUpdate();
	this->setDestroyed(true);
}

void SideArmer::setAction()
{
	action = Sequence::create(
			MoveTo::create(1.5, Point(visibleSize.width-startPoint.x, visibleSize.height*0.70)),
			MoveTo::create(1.5, Point(startPoint.x, visibleSize.height*0.40)),
			MoveTo::create(1.5, Point(visibleSize.width-startPoint.x, visibleSize.height*0.10)),
			NULL);
	action->setTag(1);
}
