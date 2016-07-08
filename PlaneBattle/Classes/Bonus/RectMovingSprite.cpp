#include "RectMovingSprite.h"

RectMovingSprite::RectMovingSprite(){}

RectMovingSprite::~RectMovingSprite(){}

RectMovingSprite* RectMovingSprite::create(const std::string& filename)
{
    RectMovingSprite *pRet = new(std::nothrow) RectMovingSprite();
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

bool RectMovingSprite::init()
{
//	if(!Sprite::init())
//		return false;

	visibleSize = Director::getInstance()->getVisibleSize();

	switch(std::rand()%4)
	{
	case 0:
		{
			startPoint.x = (std::rand()%99+1) / (float)100.0 * visibleSize.width;
			startPoint.y = visibleSize.height;
			position = up;
//			log("__________________up  %f", startPoint.x);
			break;
		}
	case 1:
		{
			startPoint.x = (std::rand()%99+1) / (float)100.0 * visibleSize.width;
			startPoint.y = 0;
			position = down;
//			log("________________down  %f", startPoint.x);
			break;
		}
	case 2:
		{
			startPoint.x = 0;
			startPoint.y = (std::rand()%99+1) / (float)100.0 * visibleSize.height;
			position = left;
//			log("________________left  %f", startPoint.y);
			break;
		}
	case 3:
		{
			startPoint.x = visibleSize.width;
			startPoint.y = (std::rand()%99+1) / (float)100.0 * visibleSize.height;
			position = right;
//			log("_______________right  %f", startPoint.y);
			break;
		}
	}

	this->setPosition(startPoint);

	// 0.50 is similar to pie/6, 1.50 is similar to pie/2
	slope = tan((CCRANDOM_0_1()+0.5) * (std::rand()%2?1:-1));
	nextPoint = getNextPoint();

	speed =	0.05;
	delay = 3.0;

	return true;
}

void RectMovingSprite::update(float dt)
{
	if(this->getPosition() == nextPoint)
	{
		if(nextPoint.x == 0)
		{
			position = left;
		}
		else if(nextPoint.x == visibleSize.width)
		{
			position = right;
		}
		else if(nextPoint.y == 0)
		{
			position = down;
		}
		else if(nextPoint.y == visibleSize.height)
		{
			position = up;
		}

		startPoint = nextPoint;
		nextPoint = getNextPoint();

		this->runAction(MoveTo::create(getMovingTime(), nextPoint));
	}
}

bool RectMovingSprite::start()
{
	this->runAction(Sequence::create(
			DelayTime::create(delay),
			MoveTo::create(getMovingTime(), nextPoint),
			NULL
	));
	this->scheduleUpdate();

	return true;
}

Point RectMovingSprite::getNextPoint()
{
	Point temp;

	// if Sprite moves from the corners
	if(startPoint == Point(0, 0))
	{
		position = down;
		slope = tan(CCRANDOM_0_1()+0.5);

		if((visibleSize.width - startPoint.x) * slope > visibleSize.height)
		{
			temp.x = startPoint.x + visibleSize.height / slope;
			temp.y = visibleSize.height;
			slope = -slope;
		}
		else
		{
			temp.x = visibleSize.width;
			temp.y = startPoint.x * slope;
			slope = 1 / slope;
		}
		return temp;
	}
	else if(startPoint == Point(0, visibleSize.height))
	{
		position = up;
		slope = -tan(CCRANDOM_0_1()+0.5);

		if((visibleSize.width - startPoint.x) * (-slope) > visibleSize.height)
		{
			temp.x = startPoint.x + visibleSize.height / (-slope);
			temp.y = 0;
			slope = -slope;
		}
		else
		{
			temp.x = visibleSize.width;
			temp.y = visibleSize.height - (visibleSize.width - startPoint.x) * (-slope);
			slope = 1 / slope;
		}
		return temp;
	}
	else if(startPoint == Point(visibleSize.width, 0))
	{
		position = down;
		slope = -tan(CCRANDOM_0_1()+0.5);

		if(startPoint.x * (-slope) > visibleSize.height)
		{
			temp.x = startPoint.x - visibleSize.height / (-slope);
			temp.y = visibleSize.height;
			slope = -slope;
		}
		else
		{
			temp.x = 0;
			temp.y = startPoint.x * (-slope);
			slope = 1 / slope;
		}
		return temp;
	}
	else if(startPoint == Point(visibleSize.width, visibleSize.height))
	{
		position = up;
		slope = tan(CCRANDOM_0_1()+0.5);

		if(startPoint.x * slope > visibleSize.height)
		{
			temp.x = startPoint.x - visibleSize.height / slope;
			temp.y = 0;
			slope = -slope;
		}
		else
		{
			temp.x = 0;
			temp.y = visibleSize.height - startPoint.x * slope;
			slope = 1 / slope;
		}
		return temp;
	}

	// Sprite not moves from the corners
	switch(position)
	{
	case up:
	{
		if(slope > 0)
		{
			if(startPoint.x * slope > visibleSize.height)
			{
				temp.x = startPoint.x - visibleSize.height / slope;
				temp.y = 0;
				slope = -slope;
			}
			else
			{
				temp.x = 0;
				temp.y = visibleSize.height - startPoint.x * slope;
				slope = 1 / slope;
			}
		}
		else
		{
			if((visibleSize.width - startPoint.x) * (-slope) > visibleSize.height)
			{
				temp.x = startPoint.x + visibleSize.height / (-slope);
				temp.y = 0;
				slope = -slope;
			}
			else
			{
				temp.x = visibleSize.width;
				temp.y = visibleSize.height - (visibleSize.width - startPoint.x) * (-slope);
				slope = 1 / slope;
			}
		}
		break;
	}
	case down:
	{
		if(slope > 0)
		{
			if((visibleSize.width - startPoint.x) * slope > visibleSize.height)
			{
				temp.x = startPoint.x + visibleSize.height / slope;
				temp.y = visibleSize.height;
				slope = -slope;
			}
			else
			{
				temp.x = visibleSize.width;
				temp.y = (visibleSize.width - startPoint.x) * slope;
				slope = 1 / slope;
			}
		}
		else
		{
			if(startPoint.x * (-slope) > visibleSize.height)
			{
				temp.x = startPoint.x - visibleSize.height / (-slope);
				temp.y = visibleSize.height;
				slope = -slope;
			}
			else
			{
				temp.x = 0;
				temp.y = startPoint.x * (-slope);
				slope = 1 / slope;
			}
		}
		break;
	}
	case left:
	{
		if(slope > 0)
		{
			if(startPoint.y * slope > visibleSize.width)
			{
				temp.x = visibleSize.width;
				temp.y = startPoint.y - visibleSize.width / slope;
				slope = -slope;
			}
			else
			{
				temp.x = startPoint.y * slope;
				temp.y = 0;
				slope = 1 / slope;
			}
		}
		else
		{
			if((visibleSize.height-startPoint.y)*(-slope) > visibleSize.width)
			{
				temp.x = visibleSize.width;
				temp.y = startPoint.y + visibleSize.width / (-slope);
				slope = -slope;
			}
			else
			{
				temp.x = (visibleSize.height-startPoint.y) * (-slope);
				temp.y = visibleSize.height;
				slope = 1 / slope;
			}
		}
		break;
	}
	case right:
	{
		if(slope > 0)
		{
			if((visibleSize.height-startPoint.y) * slope > visibleSize.width)
			{
				temp.x = 0;
				temp.y = startPoint.y + visibleSize.width / slope;
				slope = -slope;
			}
			else
			{
				temp.x = visibleSize.width - (visibleSize.height-startPoint.y) * slope;
				temp.y = visibleSize.height;
				slope = 1 / slope;
			}
		}
		else
		{
			if(startPoint.y * (-slope) > visibleSize.width)
			{
				temp.x = 0;
				temp.y = startPoint.y - visibleSize.width / (-slope);
				slope = -slope;
			}
			else
			{
				temp.x = visibleSize.width - startPoint.y * (-slope);
				temp.y = 0;
				slope = 1 / slope;
			}
		}
		break;
	}
	}

	return temp;
}

float RectMovingSprite::getMovingTime()
{
	float distance = sqrt(pow(nextPoint.x-startPoint.x, 2) + pow(nextPoint.y-startPoint.y, 2));
	return distance / visibleSize.width * speed;
}
