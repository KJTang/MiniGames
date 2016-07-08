#include "GameScene.h"
#include "GameOverScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

GameScene* GameScene::gameScene = NULL;

bool GameScene::init()
{
	startBefore = false;

	backgroundLayer = BackgroundLayer::create();
	if(backgroundLayer)
	{
		this->addChild(backgroundLayer);
	}

	gameLayer = GameLayer::create();
	if(gameLayer)
	{
		this->addChild(gameLayer);
	}

	menuLayer = MenuLayer::create();
	if(menuLayer)
	{
		this->addChild(menuLayer);
	}

	textLayer = TextLayer::create();
	if(textLayer)
	{
		this->addChild(textLayer);
	}

	return true;
}

void GameScene::onEnter()
{
	Scene::onEnter();
	this->scheduleUpdate();
}

void GameScene::update(float dt)
{
	// Change the score
	if(gameLayer->needUpdateScore)
	{
		textLayer->updateScore(gameLayer->shotScore);
		gameLayer->needUpdateScore = false;
	}
	// game win
	if(gameLayer->isWin)
	{
		gameLayer->isWin = false;
		// 储存数据
		std::string defaultname = "Default";
		UserData::addData(defaultname, gameLayer->shotScore);
		Director::getInstance()->purgeCachedData();
		auto scene = TransitionFade::create(1, GameOverScene::create(true));
		Director::getInstance()->replaceScene(scene);
	}
	// game over
	if(gameLayer->isOver)
	{
		gameLayer->isOver = false;
		gameLayer->pauseMusic();
		// 储存数据
		std::string defaultname = "Default";
		UserData::addData(defaultname, gameLayer->shotScore);
		Director::getInstance()->purgeCachedData();
		auto scene = TransitionFade::create(1, GameOverScene::create(false));
		Director::getInstance()->replaceScene(scene);
	}
}

void GameScene::restart()
{
//    this->removeAllChildrenWithCleanup(true); // Dont know why when use this will cause bug
	this->removeChild(backgroundLayer);
	this->removeChild(menuLayer);
	this->removeChild(textLayer);
	this->removeChild(gameLayer);
    this->init();
}

