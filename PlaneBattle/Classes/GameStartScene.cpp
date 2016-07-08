#include "GameStartScene.h"

#include "GameScene.h"
#include "ScoreScene.h"

using namespace cocos2d::ui;

GameStartScene::GameStartScene()
{
}

GameStartScene::~GameStartScene()
{
}

bool GameStartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getWinSize();

	startlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(startlayer);

	// Title
	auto title = Label::createWithSystemFont("PlaneBattle", "AppleGothic", visibleSize.width / 5,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	title->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 3));
//	title->setTextColor(Color4B(255, 255, 255, 0));
	startlayer->addChild(title);

	btn_start = Button::create();
	btn_start->setTouchEnabled(true);
	btn_start->setPressedActionEnabled(true);
	btn_start->loadTextures("button/start1.png", "button/start2.png");
	auto btnSize = btn_start->getContentSize();
	float rate = visibleSize.width / btnSize.width / 2.75;
	btn_start->setScale(rate);
	btn_start->setPosition(
			Point(visibleSize.width / 2,
					visibleSize.height / 2 - btnSize.height * rate * (0.5 + 0.2)));

	btn_score = Button::create();
	btn_score->setTouchEnabled(true);
	btn_score->setPressedActionEnabled(true);
	btn_score->loadTextures("button/score1.png", "button/score2.png");
	btn_score->setScale(rate);
	btn_score->setPosition(
			Point(visibleSize.width / 2,
					btn_start->getPositionY() - btnSize.height * rate * (1 + 0.2)));

	btn_quit = Button::create();
	btn_quit->setTouchEnabled(true);
	btn_quit->setPressedActionEnabled(true);
	btn_quit->loadTextures("button/quit1.png", "button/quit2.png");
	btn_quit->setScale(rate);
	btn_quit->setPosition(
			Point(visibleSize.width / 2,
					btn_score->getPositionY() - btnSize.height * rate * (1 + 0.2)));

	startlayer->addChild(btn_start);
	startlayer->addChild(btn_score);
	startlayer->addChild(btn_quit);

	return true;
}

void GameStartScene::onEnter()
{
	Scene::onEnter();
	btn_start->addTouchEventListener(startlayer,
			toucheventselector(GameStartScene::startButton));
	btn_score->addTouchEventListener(startlayer,
			toucheventselector(GameStartScene::scoreButton));
	btn_quit->addTouchEventListener(startlayer,
			toucheventselector(GameStartScene::quitButton));
}

void GameStartScene::startButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		Director::getInstance()->purgeCachedData();
		if(GameScene::getInstance()->isStartBefore())
		{
			GameScene::getInstance()->restart();
		}
		auto scene = TransitionFade::create(1, GameScene::getInstance());
		Director::getInstance()->replaceScene(scene);
		break;
	}
	default:
		break;
	}
}

void GameStartScene::scoreButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		Director::getInstance()->purgeCachedData();
		auto scene = TransitionFade::create(1, ScoreScene::create());
		Director::getInstance()->replaceScene(scene);
		break;
	}
	default:
		break;
	}
}

void GameStartScene::quitButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		Director::getInstance()->end();
		break;
	}
	default:
		break;
	}
}
