#pragma once
#include "cocos2d.h"
USING_NS_CC;

//GameStatus
enum GAME_STATUS{
	GAME_READY,
	GAME_START,
	GAME_OVER
};

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	GAME_STATUS gameStatus;
	Sprite *birdSprite;
	Action *swingAction;
};