#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class ButtonSprite : public Sprite
{
private:
    cocos2d::Size visibleSize;
    Sprite *btnPressed, *btnReleased;
    EventListenerTouchOneByOne* touchListener;
    Point startPoint, endPoint;
    std::function<void()> callbackFunc;
public:
    ButtonSprite();
    ~ButtonSprite();

    static ButtonSprite* create(const std::string &released, const std::string &pressed);

    virtual bool init(const std::string &released, const std::string &pressed);
    virtual void onEnter();

    virtual void onClicked();
    void setCallbackFunc(const std::function<void()> &callbackFunc);
};
