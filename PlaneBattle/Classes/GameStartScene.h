#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameStartScene : public Scene
{
private:
	Layer * startlayer;
	Button * btn_start;
	Button * btn_score;
	Button * btn_quit;
	Size visibleSize;
public:
	GameStartScene();
	~GameStartScene();

	bool init();
	void onEnter();
	CREATE_FUNC(GameStartScene);

	// Buttons
	void startButton(Ref *pSender, TouchEventType type);
	void scoreButton(Ref *pSender, TouchEventType type);
	void quitButton(Ref *pSender, TouchEventType type);
};
