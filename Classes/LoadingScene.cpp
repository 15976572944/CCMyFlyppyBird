#include "LoadingScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


bool LoadingScene::init()
{
	if (Scene::init())
		return true;
	else
		return false;
}

void LoadingScene::onEnter() {
	//取得屏幕尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//起始点
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//载入背景图
	auto splashBg = Sprite::create("splash.png");
	splashBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(splashBg);

	//logo文字
	auto logo = LabelTTF::create("by Robin", "Arial", 20);
	logo->setColor(Color3B(0, 255, 0));
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 50);
	this->addChild(logo);
	
	//get纹理：其实就是读取美术资源
	Director::getInstance()->getTextureCache()->addImageAsync("game.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(Texture2D *texture){

	//载入多个精灵帧    - -！ 官方说法不好懂的样子
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist", texture);

	//帧动画，小鸟飞
	auto birdAnimation = Animation::create();
	birdAnimation->setDelayPerUnit(0.2f);
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird1.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird2.png"));
	birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird3.png"));
	AnimationCache::getInstance()->addAnimation(birdAnimation, "birdAnimation");
	
	//声音
	SimpleAudioEngine::getInstance()->preloadEffect("die.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("hit.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("swooshing.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("wing.mp3");
	
	//载入完成之后跳转到gamescene
	auto gameScene = GameScene::createScene();
	TransitionScene *transition = TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(transition);
}