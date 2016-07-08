#pragma once

#include "cocos2d.h"
#include "PlayerSprite.h"
#include "ButtonSprite.h"
#include "SocketTest.h"
#include "AudioRecord.h"

using namespace cocos2d;

class PKScene : public Scene
{
private:
    Size visibleSize;
    Layer *backgroundLayer;
    SocketTest *socketLayer;
    PlayerSprite *myPlayer, *otherPlayer;
    Sprite *num[3];
    bool isPrepared;
public:
    PKScene() {}
    ~PKScene() {}
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(PKScene);

    void OnPrepare();
    void OnVoice();
    void OnPK();
    void OnPKEnd(bool isWin);
};