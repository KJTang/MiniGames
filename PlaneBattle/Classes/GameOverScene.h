#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameOverScene : public Scene
{
private:
	Layer * gameoverlayer;
	Button * btn_start;
	Button * btn_return;
	Button * btn_quit;
	Size visibleSize;

	bool isWin;
public:
	GameOverScene();
	~GameOverScene();

	bool init();
	void onEnter();
	static GameOverScene* create(bool b);

	void setWinFlag(bool b) { isWin = b;}

	// Buttons
	void startButton(Ref *pSender, TouchEventType type);
	void returnButton(Ref *pSender, TouchEventType type);
	void quitButton(Ref *pSender, TouchEventType type);
};
