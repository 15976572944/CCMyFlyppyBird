#pragma once
#include "cocos2d.h"
USING_NS_CC;

const int BIRD_RADIUS = 15; //–°ƒÒ∞Îæ∂
const int PIPE_HEIGHT = 320;//∞Î∏˘π‹µ¿≥§∂»
const int PIPE_WIDTH = 52; //π‹µ¿øÌ∂»
const int PIPE_SPACE = 100; //…œœ¬π‹÷Æº‰µƒ∑Ïœ∂
const int PIPE_INTERVAL = 170;//∫·œÚ¡Ω∏˘π‹◊”÷Æº‰µƒº‰æ‡,288/2+52/2
const int WAIT_DISTANCE = 380;//µ»¥˝æ‡¿Î

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
	void update(float dt);
	void setPhysicWorld(cocos2d::PhysicsWorld *world);
	void scrollLand(float dt);
	
	virtual bool onContactBegin(const cocos2d::PhysicsContact& contact);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void createPipes();
	void gameStart();
	void gameOver();
	int getRandomHeight();
	
private:
	GAME_STATUS gameStatus;
	Sprite *birdSprite;
	Action *swingAction;
	Sprite *land1, *land2;
	Vector<cocos2d::Node*> pipes;
	PhysicsWorld *m_physicWorld;
	int touchX;
};