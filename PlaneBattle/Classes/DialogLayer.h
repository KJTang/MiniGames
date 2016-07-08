#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class DialogLayer : public Layer
{
private:
	Size visibleSize;
	Layer *background;
	Button *btn_yes, *btn_no;
public:
	DialogLayer();
	~DialogLayer();

	virtual bool init();
	CREATE_FUNC(DialogLayer);

	virtual void onEnter();

	void enable();
	void disable();

	void yesButton(Ref *pSender, TouchEventType type);
	void noButton(Ref *pSender, TouchEventType type);
};
