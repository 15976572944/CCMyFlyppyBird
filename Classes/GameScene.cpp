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
	gameScene->getPhysicsWorld()->setGravity(Vec2(0, -900)); //设置重力场,重力加速度可以根据手感改小点
	
	//添加主游戏层
	auto gameLayer = GameScene::create();
//	gameLayer->setPhysicWorld(gameScene->getPhysicsWorld()); //绑定物理世界
	gameScene->addChild(gameLayer);
	return gameScene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point visibleOrigin = Director::getInstance()->getVisibleOrigin();

	//back ground
	Sprite *backGround = Sprite::createWithSpriteFrameName("bg.png");
	backGround->setPosition(visibleOrigin.x + visibleSize.width /2, visibleOrigin.y + visibleSize.height /2);
	this->addChild(backGround);
	
	//logo
	auto gameLogo = Sprite::createWithSpriteFrameName("bird_logo.png");
	gameLogo->setPosition(visibleOrigin.x + visibleSize.width /2, visibleOrigin.y + visibleSize.height /2+100);
	this->addChild(gameLogo);
	return true;
}

