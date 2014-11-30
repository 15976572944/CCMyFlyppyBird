#include "LoadingScene.h"


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
}

void LoadingScene::loadingCallBack(Texture2D *texture){
	
}