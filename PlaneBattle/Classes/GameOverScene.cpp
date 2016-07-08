#include "GameOverScene.h"

#include "GameScene.h"
#include "GameStartScene.h"
#include "TextLayer.h"

using namespace cocos2d::ui;

GameOverScene::GameOverScene(){}

GameOverScene::~GameOverScene(){}

GameOverScene* GameOverScene::create(bool b)
{
    GameOverScene *pRet = new(std::nothrow) GameOverScene();
    pRet->setWinFlag(b);
    if (pRet && pRet->init())
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

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	gameoverlayer = LayerColor::create(Color4B::BLACK);
	this->addChild(gameoverlayer);

	// Title
	Label *title = NULL;
	if(isWin)
	{
		title = Label::createWithSystemFont("Game Win!", "AppleGothic", visibleSize.width / 6,
				Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	}
	else
	{
		title = Label::createWithSystemFont("Game Over", "AppleGothic", visibleSize.width / 6,
				Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	}
	title->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 3));
	gameoverlayer->addChild(title);

	// Score
	auto score = Label::createWithSystemFont("Your Score: "+TextLayer::getScore(), "AppleGothic", visibleSize.width / 14,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	score->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 8 * 5));
	gameoverlayer->addChild(score);

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

	btn_return = Button::create();
	btn_return->setTouchEnabled(true);
	btn_return->setPressedActionEnabled(true);
	btn_return->loadTextures("button/return1.png", "button/return2.png");
	btn_return->setScale(rate);
	btn_return->setPosition(
			Point(visibleSize.width / 2,
					btn_start->getPositionY() - btnSize.height * rate * (1 + 0.2)));

	btn_quit = Button::create();
	btn_quit->setTouchEnabled(true);
	btn_quit->setPressedActionEnabled(true);
	btn_quit->loadTextures("button/quit1.png", "button/quit2.png");
	btn_quit->setScale(rate);
	btn_quit->setPosition(
			Point(visibleSize.width / 2,
					btn_return->getPositionY() - btnSize.height * rate * (1 + 0.2)));

	gameoverlayer->addChild(btn_start);
	gameoverlayer->addChild(btn_return);
	gameoverlayer->addChild(btn_quit);

	return true;
}

void GameOverScene::onEnter()
{
	Scene::onEnter();
	btn_start->addTouchEventListener(gameoverlayer,
			toucheventselector(GameOverScene::startButton));
	btn_return->addTouchEventListener(gameoverlayer,
			toucheventselector(GameOverScene::returnButton));
	btn_quit->addTouchEventListener(gameoverlayer,
			toucheventselector(GameOverScene::quitButton));
}

void GameOverScene::startButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		Director::getInstance()->purgeCachedData();
		GameScene::getInstance()->restart();
		auto scene = TransitionFade::create(1, GameScene::getInstance());
		Director::getInstance()->replaceScene(scene);
		break;
	}
	default:
		break;
	}
}

void GameOverScene::returnButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		Director::getInstance()->purgeCachedData();
		auto scene = TransitionFade::create(1, GameStartScene::create());
		Director::getInstance()->replaceScene(scene);
		break;
	}
	default:
		break;
	}
}

void GameOverScene::quitButton(Ref *pSender, TouchEventType type)
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
