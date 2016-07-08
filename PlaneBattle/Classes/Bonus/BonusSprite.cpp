#include "BonusSprite.h"

BonusSprite::BonusSprite(){}

BonusSprite::~BonusSprite(){}

BonusSprite* BonusSprite::create(const std::string& filename)
{
    BonusSprite *pRet = new(std::nothrow) BonusSprite();
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

Rect BonusSprite::getRect()
{
	return this->getBoundingBox();
}
