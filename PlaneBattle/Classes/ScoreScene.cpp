#include "ScoreScene.h"

ScoreScene::ScoreScene(){}

ScoreScene::~ScoreScene(){}

bool ScoreScene::init()
{
	if(!Scene::init())
		return false;

	visibleSize = Director::getInstance()->getWinSize();

	scorelayer = LayerColor::create(Color4B::BLACK);
	this->addChild(scorelayer);

	// Title
	auto title = Label::createWithSystemFont("Score", "AppleGothic", visibleSize.width / 5,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	title->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 8 * 7));
	scorelayer->addChild(title);

	// Score
	auto scoreRank1 = Label::createWithSystemFont(UserData::getDataName(1)+"   "+UserData::getDataScore(1),
			"AppleGothic", visibleSize.width / 10,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	scoreRank1->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 2.75));
	scorelayer->addChild(scoreRank1);

	auto scoreRank2 = Label::createWithSystemFont(UserData::getDataName(2)+"   "+UserData::getDataScore(2),
			"AppleGothic", visibleSize.width / 10,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	scoreRank2->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 2.75 - scoreRank1->getContentSize().height));
	scorelayer->addChild(scoreRank2);

	auto scoreRank3 = Label::createWithSystemFont(UserData::getDataName(3)+"   "+UserData::getDataScore(3),
			"AppleGothic", visibleSize.width / 10,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	scoreRank3->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 2.75 - scoreRank1->getContentSize().height * 2));
	scorelayer->addChild(scoreRank3);

	auto scoreRank4 = Label::createWithSystemFont(UserData::getDataName(4)+"   "+UserData::getDataScore(4),
			"AppleGothic", visibleSize.width / 10,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	scoreRank4->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 2.75 - scoreRank1->getContentSize().height * 3));
	scorelayer->addChild(scoreRank4);

	auto scoreRank5 = Label::createWithSystemFont(UserData::getDataName(5)+"   "+UserData::getDataScore(5),
			"AppleGothic", visibleSize.width / 10,
			Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	scoreRank5->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 4 * 2.75 - scoreRank1->getContentSize().height * 4));
	scorelayer->addChild(scoreRank5);

	// Button
	btn_return = Button::create();
	btn_return->setTouchEnabled(true);
	btn_return->setPressedActionEnabled(true);
	btn_return->loadTextures("button/return1.png", "button/return2.png");
	auto btnSize = btn_return->getContentSize();
	float rate = visibleSize.width / btnSize.width / 2.75;
	btn_return->setScale(rate);
	btn_return->setPosition(
			Point(visibleSize.width - btnSize.width * rate * (0.5 + 0.2),
					btnSize.height * rate * (0.5 + 0.2)));
	scorelayer->addChild(btn_return);

	btn_reset = Button::create();
	btn_reset->setTouchEnabled(true);
	btn_reset->setPressedActionEnabled(true);
	btn_reset->loadTextures("button/reset1.png", "button/reset2.png");
	btn_reset->setScale(rate);
	btn_reset->setPosition(
			Point(btnSize.width * rate * (0.5 + 0.2),
					btnSize.height * rate * (0.5 + 0.2)));
	scorelayer->addChild(btn_reset);

	return true;
}

void ScoreScene::onEnter()
{
	Scene::onEnter();
	btn_return->addTouchEventListener(scorelayer,
			toucheventselector(ScoreScene::returnButton));
	btn_reset->addTouchEventListener(scorelayer,
			toucheventselector(ScoreScene::resetButton));
}

void ScoreScene::returnButton(Ref *pSender, TouchEventType type)
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

void ScoreScene::resetButton(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
	{
		// Dialog
		dialog = DialogLayer::create();
		this->addChild(dialog);

//		btn_reset->setTouchEnabled(false);
//		btn_return->setTouchEnabled(false);

//		btn_return->onPressStateChangedToDisabled();

		break;
	}
	default:
		break;
	}
}

void ScoreScene::resetScore(bool b)
{
	if(b)
	{
		UserData::clearData();
	}
	Director::getInstance()->purgeCachedData();
	auto scene = TransitionFade::create(0.5, ScoreScene::create());
	Director::getInstance()->replaceScene(scene);
}
