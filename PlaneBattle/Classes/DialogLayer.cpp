#include "DialogLayer.h"

#include "ScoreScene.h"

DialogLayer::DialogLayer(){}

DialogLayer::~DialogLayer(){}

bool DialogLayer::init()
{
	if(!Layer::init())
		return false;

	visibleSize = Director::getInstance()->getVisibleSize();

	background = LayerColor::create(Color4B(0, 0, 0, 200));
	this->addChild(background);

	auto title = Label::createWithSystemFont("Reset Scores??", "AppleGothic", 100,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	title->setPosition(
			Point(visibleSize.width*0.5, visibleSize.height*0.75));
	background->addChild(title);

	btn_yes = Button::create();
	btn_yes->setTouchEnabled(true);
	btn_yes->setPressedActionEnabled(true);
	btn_yes->loadTextures("button/yes1.png", "button/yes2.png");
	btn_yes->setScale(
			visibleSize.width / btn_yes->getContentSize().width / 4);
	btn_yes->setPosition(
			Point(visibleSize.width*0.25, visibleSize.height*0.30));
	background->addChild(btn_yes);

	btn_no = Button::create();
	btn_no->setTouchEnabled(true);
	btn_no->setPressedActionEnabled(true);
	btn_no->loadTextures("button/no1.png", "button/no2.png");
	btn_no->setScale(
			visibleSize.width / btn_no->getContentSize().width / 4);
	btn_no->setPosition(
			Point(visibleSize.width*0.75, visibleSize.height*0.30));
	background->addChild(btn_no);

	return true;
}

void DialogLayer::onEnter()
{
	Layer::onEnter();

	btn_yes->addTouchEventListener(this,
			toucheventselector(DialogLayer::yesButton));
	btn_no->addTouchEventListener(this,
			toucheventselector(DialogLayer::noButton));
}

void DialogLayer::enable()
{
	this->setVisible(true);
}

void DialogLayer::disable()
{
	this->setVisible(false);
}

void DialogLayer::yesButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		log("YESSSSSSSSSS");
		static_cast<ScoreScene*>(this->getParent())->resetScore(true);
		break;
	}
	default:
		break;
	}
}

void DialogLayer::noButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		log("NOOOOOOOOOO");
		static_cast<ScoreScene*>(this->getParent())->resetScore(false);
		break;
	}
	default:
		break;
	}
}
