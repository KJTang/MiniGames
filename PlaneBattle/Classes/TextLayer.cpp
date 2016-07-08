#include "TextLayer.h"

using namespace cocos2d;

TextLayer::TextLayer(){}

TextLayer::~TextLayer(){}

std::string TextLayer::str_score = "00000000";

bool TextLayer::init()
{
	if(!Layer::init())
		return false;

	// 初始分数
	str_score = "00000000";

	visibleSize = Director::getInstance()->getVisibleSize();
	score = Label::createWithSystemFont("SCORE: 00000000", "AppleGothic", 50, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	score->setAnchorPoint(Point(0, 1));
	score->setPosition(Point(20, visibleSize.height - 20));
	this->addChild(score);

	return true;
}

void TextLayer::updateScore(int shotScore)
{
	str_score.clear();
	while(shotScore)
	{
		char c = shotScore%10 + 48;
		str_score += c;
		shotScore /= 10;
	}
	for(int i = str_score.size(); i < 8; i++)
	{
		str_score += '0';
	}
	std::reverse(str_score.begin(), str_score.end());
	score->setString("SCORE: " + str_score);
}

std::string TextLayer::getScore()
{
	return str_score;
}

void TextLayer::clearScore()
{
	str_score.clear();
}
