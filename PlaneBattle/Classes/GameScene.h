#pragma once

#include "cocos2d.h"

#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "MenuLayer.h"
#include "TextLayer.h"
#include "UserData.h"

using namespace cocos2d;

class GameScene : public Scene
{
private:
	static GameScene* gameScene;
	bool startBefore;

	BackgroundLayer *backgroundLayer;
	GameLayer *gameLayer;
	MenuLayer *menuLayer;
	TextLayer *textLayer;
public:
	GameScene();
	~GameScene();

	bool virtual init();
	void onEnter();
	void update(float dt);
    void restart();

	static GameScene* getInstance()
	{
		if(gameScene == NULL)
		{
			gameScene = new GameScene();
			gameScene->init();
			gameScene->setStartBefore(false);
			return gameScene;
		}

		gameScene->setStartBefore(true);
		return gameScene;
	}

	bool isStartBefore() { return startBefore;}
	void setStartBefore(bool b) { startBefore = b;}
	GameLayer* getGameLayer() { return gameLayer;}
};
