#pragma once

#include "cocos2d.h"
#include "string"

using namespace cocos2d;

class TextLayer : public Layer
{
private:
	Label *score;
	Size visibleSize;
//	TTFConfig config;
public:
	TextLayer();
	~TextLayer();
	bool init();
	void updateScore(int enemyshot);
	CREATE_FUNC(TextLayer);

	static std::string str_score;
	static std::string getScore();
	static void clearScore();
};
