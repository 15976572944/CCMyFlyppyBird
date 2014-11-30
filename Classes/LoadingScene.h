#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"




class LoadingScene : public cocos2d::Scene
{
public:
	virtual bool init();
	void onEnter();
	CREATE_FUNC(LoadingScene);
	
private:
	void loadingCallBack(cocos2d::Texture2D *texture);
};

#endif // __HELLOWORLD_SCENE_H__
