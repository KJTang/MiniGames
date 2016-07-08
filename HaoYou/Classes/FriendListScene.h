#pragma once

#include "cocos2d.h"
#include "ButtonSprite.h"

using namespace cocos2d;

class FriendListScene : public Scene
{
private:
    Size visibleSize;
    Layer *backgroundLayer, *menuLayer;
    ButtonSprite *btnBack;
public:
    FriendListScene();
    ~FriendListScene();
    virtual bool init();
    CREATE_FUNC(FriendListScene);
};