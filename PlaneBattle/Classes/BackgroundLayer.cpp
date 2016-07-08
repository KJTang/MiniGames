#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(){};

BackgroundLayer::~BackgroundLayer(){};

bool BackgroundLayer::init(){
	if(!Layer::init()){
		return false;
	}

    visibleSize = Director::getInstance()->getVisibleSize();

	//create the background
    srand(unsigned(time(0)));
    int id = rand()%5 + 1;
    char file[30];
    sprintf(file, "background/bg_%d.jpg", id);
	bg1 = Sprite::create(file);
	bg2 = Sprite::create(file);

	Size bgSize = bg1->getContentSize();

	bg1->setAnchorPoint(Point(0,0));
	bg1->setScale(visibleSize.width/bgSize.width, visibleSize.height/bgSize.height);
	bg1->setPosition(Point(0,0));

	bg2->setAnchorPoint(Point(0,0));
	bg2->setScale(visibleSize.width/bgSize.width, visibleSize.height/bgSize.height);
	bg2->setPosition(Point(0,visibleSize.height));

	this->addChild(bg1);
	this->addChild(bg2);

	return true;
}

void BackgroundLayer::onEnter()
{
	Layer::onEnter();
	this->scheduleUpdate();
}

void BackgroundLayer::update(float dt)
{
	// 背景滚动
	if(bg2->getPositionY() > 0)
	{
		bg1->setPositionY(bg1->getPositionY() - visibleSize.height/600);
		bg2->setPositionY(bg2->getPositionY() - visibleSize.height/600);
	}
	else
	{
		bg1->setPositionY(0);
		bg2->setPositionY(visibleSize.height);
	}
}
