#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class PlayerHead : public Sprite
{
private:
    Size visibleSize;
    Sprite *pic;
public:
    PlayerHead() {}
    ~PlayerHead() {}
    virtual bool init(const std::string &source);
    static PlayerHead* create(const std::string &source);
    virtual void act();
};

class PlayerBody : public Sprite
{
private:
    Size visibleSize;
    Sprite *pic;
public:
    PlayerBody(){}
    ~PlayerBody() {}
    virtual bool init(const std::string &source);
    static PlayerBody* create(const std::string &source);
    virtual void act();
};

class PlayerHand : public Sprite
{
private:
    Size visibleSize;
    Sprite *pic;
public:
    PlayerHand() {}
    ~PlayerHand() {}
    virtual bool init(const std::string &source);
    static PlayerHand* create(const std::string &source);
    virtual void act();
};

class PlayerSprite : public Sprite
{
private:
    Size visibleSize;
    PlayerHead *playerHead;
    PlayerBody *playerBody;
    PlayerHand *playerHand;
    bool direction;
public:
    int strength;
    int headinfo;
    int bodyinfo;
    int handinfo;
public:
    PlayerSprite() {}
    ~PlayerSprite() {}
    //virtual bool init(PlayerHead *head, PlayerBody *body, PlayerHand *hand, bool direction);
    //static PlayerSprite* create(PlayerHead *head, PlayerBody *body, PlayerHand *hand, bool direction = true);
    virtual bool init(bool direction);
    static PlayerSprite* create(bool direction = true);
    bool changeShape();
    void change(float dt);
    bool scaleWithVoice();
    void scale(float dt);
    void setInfo(int info);
    bool act();
};