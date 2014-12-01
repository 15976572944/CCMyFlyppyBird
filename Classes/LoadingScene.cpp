#include "LoadingScene.h"
#include "GameScene.h"

USING_NS_CC;



bool LoadingScene::init()
{
	if (Scene::init())
		return true;
	else
		return false;
}

void LoadingScene::onEnter() {
	Director::getInstance()->getTextureCache()->addImageAsync("game.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto splashBg = Sprite::create("splash.png");
	splashBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(splashBg);

	auto logo = LabelTTF::create("by Robin", "Arial", 20);
	logo->setColor(Color3B(0, 255, 0));
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 50);
	this->addChild(logo);

	Director::getInstance()->getTextureCache()->addImageAsync("game.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(Texture2D *texture){
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist", texture);
//	auto birdAnimation = Animation::create();
//	birdAnimation->setDelayPerUnit(0.2f);
//	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird1.png"));
//	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird2.png"));
//	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird3.png"));
//	AnimationCache::getInstance()->addAnimation(birdAnimation, "birdAnimation");
//	
//	auto gameScene = GameScene::createScene();
//	TransitionScene *transition = TransitionFade::create(0.5f,gameScene);
//	Director::getInstance()->replaceScene(transition);
}