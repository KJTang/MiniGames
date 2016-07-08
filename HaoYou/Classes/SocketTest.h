#ifndef __SOCKET_TEST_H__
#define __SOCKET_TEST_H__

#include "cocos2d.h"

USING_NS_CC;

class SocketTest : public Layer
{
public:
    virtual bool init();
    
	CREATE_FUNC(SocketTest);
	
	
	void FirstStart();

	void NextStart();

	int FirstAtk(int atk);

	int NextAtk(int atk);

	
};

#endif