#include "MenuLayer.h"
#include "GameStartScene.h"
#include "GameScene.h"

MenuLayer::MenuLayer(){}

MenuLayer::~MenuLayer(){}

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 获取窗口大小以及原点坐标
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// 暂停背景
	pauselayer = LayerColor::create(Color4B(0, 0, 0, 180));
	this->addChild(pauselayer);
	pauselayer->setVisible(false);

	// Title
	auto title = Label::createWithSystemFont("Paused", "AppleGothic", visibleSize.width / 5,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	title->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 3));
	pauselayer->addChild(title);

	btn_pause = Button::create();
	btn_pause->setTouchEnabled(true);
	btn_pause->setPressedActionEnabled(true);
	btn_pause->loadTextures("button/pause1.png", "button/pause1.png");
	btn_pause->setScale(
			visibleSize.width / btn_pause->getContentSize().width / 12);
	btn_pause->setPosition(
			Point(visibleSize.width - btn_pause->getContentSize().width * 2,
					btn_pause->getContentSize().height * 2));

	btn_resume = Button::create();
	btn_resume->setTouchEnabled(false);
	btn_resume->setPressedActionEnabled(true);
	btn_resume->loadTextures("button/pause2.png", "button/pause2.png");
	btn_resume->setScale(
			visibleSize.width / btn_resume->getContentSize().width / 12);
	btn_resume->setPosition(
			Point(visibleSize.width - btn_resume->getContentSize().width * 2,
					btn_resume->getContentSize().height * 2));

	btn_pause->setVisible(true);
	btn_resume->setVisible(false);
	this->addChild(btn_pause);
	this->addChild(btn_resume);

	btn_menu = Button::create();
	btn_menu->setTouchEnabled(true);
	btn_menu->loadTextures("button/menu1.png", "button/menu2.png");
	auto rate = visibleSize.width / btn_menu->getContentSize().width / 2.75; //
	btn_menu->setScale(rate);
	auto btnSize = btn_menu->getContentSize();
	btn_menu->setPosition(
			Point(visibleSize.width / 2,
					visibleSize.height / 2 + btnSize.height/2));

	btn_back = Button::create();
	btn_back->setTouchEnabled(true);
	btn_back->loadTextures("button/back1.png", "button/back2.png");
	btn_back->setScale(rate);
	btn_back->setPosition(
			Point(visibleSize.width / 2,
					visibleSize.height / 2 - btnSize.height*1.5));

	pauselayer->addChild(btn_menu);
	pauselayer->addChild(btn_back);

	return true;
}

void MenuLayer::onEnter()
{
	Layer::onEnter();
	btn_pause->addTouchEventListener(this,
			toucheventselector(MenuLayer::pauseButton));
	btn_resume->addTouchEventListener(this,
			toucheventselector(MenuLayer::resumeButton));
	btn_menu->addTouchEventListener(this,
			toucheventselector(MenuLayer::menuButton));
	btn_back->addTouchEventListener(this,
			toucheventselector(MenuLayer::backButton));
}

void MenuLayer::pauseButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		if (!Director::getInstance()->isPaused())
		{
			btn_pause->setVisible(false);
			btn_pause->setTouchEnabled(false);
			btn_resume->setVisible(true);
			btn_resume->setTouchEnabled(true);
			pauselayer->setVisible(true);
			GameScene::getInstance()->getGameLayer()->pauseMusic();
			Director::getInstance()->pause();
		}
		break;
	}
	default:
		break;
	}
}

void MenuLayer::resumeButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		if (Director::getInstance()->isPaused())
		{
			btn_pause->setVisible(true);
			btn_pause->setTouchEnabled(true);
			btn_resume->setVisible(false);
			btn_resume->setTouchEnabled(false);
			pauselayer->setVisible(false);
			Director::getInstance()->resume();
			GameScene::getInstance()->getGameLayer()->resumeMusic();
		}
		break;
	}
	default:
		break;
	}
}

void MenuLayer::menuButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		Director::getInstance()->resume();
		Director::getInstance()->purgeCachedData();
		auto scene = TransitionFade::create(1, GameStartScene::create());
		Director::getInstance()->replaceScene(scene);
		break;
	}
	default:
		break;
	}
}

void MenuLayer::backButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		if (Director::getInstance()->isPaused())
		{
			btn_pause->setVisible(true);
			btn_pause->setTouchEnabled(true);
			btn_resume->setVisible(false);
			btn_resume->setTouchEnabled(false);
			pauselayer->setVisible(false);
			Director::getInstance()->resume();
		}
		break;
	}
	default:
		break;
	}
}
