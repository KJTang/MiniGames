#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class MenuLayer : public Layer
{
private:
    Layer *pauselayer;
    Button *btn_pause, *btn_resume, *btn_menu, *btn_back;
public:
	MenuLayer();
	~MenuLayer();
	bool init();
	void onEnter();
	CREATE_FUNC(MenuLayer);

	// Buttons
	void pauseButton(Ref *pSender, TouchEventType type);
	void resumeButton(Ref *pSender, TouchEventType type);
	void menuButton(Ref *pSender, TouchEventType type);
	void backButton(Ref *pSender, TouchEventType type);
};
