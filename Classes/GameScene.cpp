/*
* Robin
* 20141202
*/
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* GameScene::createScene()
{
	//
	auto gameScene = Scene::createWithPhysics();
	gameScene->getPhysicsWorld()->setGravity(Vec2(0, -900)); //
	
	//
	auto gameLayer = GameScene::create();
//	gameLayer->setPhysicWorld(gameScene->getPhysicsWorld()); //
	gameScene->addChild(gameLayer);
	return gameScene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point visibleOrigin = Director::getInstance()->getVisibleOrigin();

	//游戏准备开始
	gameStatus = GAME_READY;
	//back ground
	Sprite *backGround = Sprite::createWithSpriteFrameName("bg.png");
	backGround->setPosition(visibleOrigin.x + visibleSize.width /2, visibleOrigin.y + visibleSize.height /2);
	this->addChild(backGround);
	
	//logo
	auto gameLogo = Sprite::createWithSpriteFrameName("bird_logo.png");
	gameLogo->setPosition(visibleOrigin.x + visibleSize.width /2, visibleOrigin.y + visibleSize.height /2+100);
	this->addChild(gameLogo);
	
	//小鸟
	birdSprite = Sprite::create();
	birdSprite->setPosition(visibleOrigin.x + visibleSize.width / 3, visibleOrigin.y + visibleSize.height /2);
	this->addChild(birdSprite);
	
	//翅膀
	auto birdAnim= Animate::create(AnimationCache::getInstance()->animationByName("birdAnimation"));
	birdSprite->runAction(RepeatForever::create(birdAnim));
	auto up = MoveBy::create(0.4f, Point(0,8));
	auto upBack = up->reverse();
	//上下晃动
	if (gameStatus == GAME_READY)
	{
		swingAction = RepeatForever::create(Sequence::create(up,upBack, NULL));
		birdSprite->runAction(swingAction);
	}
	return true;
	
}

