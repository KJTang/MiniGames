#include "FloatingTextSprite.h"

FloatingTextSprite::FloatingTextSprite(){}

FloatingTextSprite::~FloatingTextSprite(){}

bool FloatingTextSprite::init()
{
	if(!Layer::init())
		return false;

	visibleSize = Director::getInstance()->getVisibleSize();
	action = Spawn::create(
			MoveBy::create(2, Point(0, 200)),
			FadeOut::create(2),
			NULL);
	action->setTag(1);

	textLabel = Label::createWithSystemFont("Nothing", "AppleGothic", 200,
					Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	textLabel->setPosition(Point(visibleSize.width*0.50, visibleSize.height*0.75));
	textLabel->setTextColor(Color4B(255, 255, 255, 255));

	this->addChild(textLabel);

	return true;
}

void FloatingTextSprite::update(float dt)
{
	if(textLabel->getActionByTag(1) && !textLabel->getActionByTag(1)->isDone())
	{
		return;
	}

	remove();
}
