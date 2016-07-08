#include "ArmerSprite.h"

ArmerSprite::ArmerSprite(){}

ArmerSprite::~ArmerSprite(){}

ArmerSprite* ArmerSprite::create(const std::string& filename)
{
    ArmerSprite *pRet = new(std::nothrow) ArmerSprite();
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

bool ArmerSprite::init()
{
	destroyed = false;

	setLife(1);
	setScore(1);
	setAction();

	startPoint = Point(0, 0);

	return true;
}

void ArmerSprite::update()
{

}

void ArmerSprite::setStartPoint(Point p)
{
	// if don't use the default point
	if(p != Point(-1, -1))
	{
		startPoint = p;
		setPosition(startPoint);
		setAction();
	}
}

void ArmerSprite::setAction()
{
	action = DelayTime::create(0.1);
}
