#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "GameStartScene.h"
#include "DialogLayer.h"
#include "UserData.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class ScoreScene : public Scene
{
private:
	Size visibleSize;
	Layer * scorelayer;
	DialogLayer *dialog;
	Button * btn_return;
	Button * btn_reset;
public:
	ScoreScene();
	~ScoreScene();

	bool init();
	void onEnter();
	CREATE_FUNC(ScoreScene);

	void returnButton(Ref *pSender, TouchEventType type);
	void resetButton(Ref *pSender, TouchEventType type);

	void resetScore(bool b);
};
