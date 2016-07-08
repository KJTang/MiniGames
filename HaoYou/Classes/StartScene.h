#pragma once

#include "cocos2d.h"
#include "ButtonSprite.h"

using namespace cocos2d;

class StartScene : public Scene
{
private:
    Size visibleSize;
    Layer *backgroundLayer, *menuLayer;
    ButtonSprite *btnPK, *btnStore, *btnFriend;
public:
    StartScene();
    ~StartScene();
    virtual bool init();
    CREATE_FUNC(StartScene);
};

