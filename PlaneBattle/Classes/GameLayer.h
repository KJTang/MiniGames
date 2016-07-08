#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>
#include <ctime>

#include "PlayerSprite.h"
#include "Bonus/BonusSprite.h"
#include "EnemySprite.h"
#include "GameBarrier.h"
#include "FloatingTextSprite.h"

using namespace cocos2d;
// SimpleAudioEngine所在namespace
using namespace CocosDenshion;

class GameLayer : public Layer
{
private:
    Size visibleSize;
    Vec2 origin;
	PlayerSprite*  player;
	BonusSprite*  bonus;
	int gamelevel;
	// 用于播放动画的Sprite
	Vector<Sprite*> AnimationSprite;
	// 触屏移动飞机时触摸点与飞机点的距离
	double deltax;
	double deltay;

	bool weaponChanged;
	int playerWeaponLevel;
	// 奖励
	bool bonusApeared;
public:
	GameLayer();
	~GameLayer();

	bool init();
	void update(float dt);
	void onEnter();
	CREATE_FUNC(GameLayer);

	// 击中敌机
	bool needUpdateScore;
	int shotScore;
	// 游戏控制
	bool isWin;
	bool isOver;

	// 敌人
	Vector <EnemySprite*> enemys;
	void createEnemy(std::vector<myEnemy> v);
	void removeEnemy(EnemySprite *pEnemy);
	// 奖励
	void createBonus();
	void removeBonus(BonusSprite *pBonus);
	// 碰撞检测
	void collision();
	// 播放爆炸动画
	void playAnimation(Point Position);
	// 游戏控制
	int getGameLevel() {return gamelevel;}
	void playMusic() { SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm.mp3", true);}
	void pauseMusic() {	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();}
	void resumeMusic() { SimpleAudioEngine::getInstance()->resumeBackgroundMusic();}
	void GameWin();
	void GameOver();

	// 点击事件响应函数
	bool onTouchBegan(Touch *touch, Event *pEvent);
	void onTouchMoved(Touch *touch, Event *pEvent);
	void onTouchEnded(Touch *touch, Event *pEvent);
	void onTouchCancelled(Touch *touch, Event *pEvent);
};
