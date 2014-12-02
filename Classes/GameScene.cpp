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
	gameScene->getPhysicsWorld()->setGravity(Vec2(0, -900)); //����������,�������ٶȿ��Ը����ָи�С��
	
	//�������Ϸ��
	auto gameLayer = GameScene::create();
//	gameLayer->setPhysicWorld(gameScene->getPhysicsWorld()); //����������
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

