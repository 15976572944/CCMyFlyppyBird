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
	gameLayer->setPhysicWorld(gameScene->getPhysicsWorld()); //∞Û∂®ŒÔ¿Ì ¿ΩÁ
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
	gameLogo->setName("logo");
	this->addChild(gameLogo);
	
	createPipes();
	
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
	
	//小鸟绑定纲体
	auto birdBody = PhysicsBody::createCircle(BIRD_RADIUS);//将小鸟当成圆
	birdBody->setDynamic(true);//设置为可以被物理场所作用而动作
	birdBody->setContactTestBitmask(1);//必须设置这项为1才能监测到不同物体的碰撞
	birdBody->setGravityEnable(false);//设置是否被重力影响，准备画面种不收重力影响
	birdSprite->setPhysicsBody(birdBody);//为小鸟设置纲体
	
	//上下管道
	land1 = Sprite::createWithSpriteFrameName("land.png");
	land1->setAnchorPoint(Point::ZERO);
	land1->setPosition(Point::ZERO);
	//第二个参数是order，表示在第几层
	this->addChild(land1,10);
	land2 = Sprite::createWithSpriteFrameName("land.png");
	land2->setAnchorPoint(Point::ZERO);
	land2->setPosition(Point::ZERO);
	this->addChild(land2,10);
	
	Node *groundNode = Node::create();
	auto groundBody = PhysicsBody::createBox(Size(visibleSize.width, land1->getContentSize().height));
	groundBody->setDynamic(false);
	groundBody->setContactTestBitmask(1);
	groundNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE); //物理引擎种的纲体只允许结点锚点设置为中心
	groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(visibleOrigin.x+visibleSize.width/2,land1->getContentSize().height/2);
	this->addChild(groundNode);
	
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//地图
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	//ÃÌº”¥•√˛º‡Ã˝
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
	
}

void GameScene::scrollLand(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//两个图片循环移动组成不断转动的地板
	land1->setPositionX(land1->getPositionX() - 1.0f);
	land2->setPositionX(land1->getPositionX() + land1->getContentSize().width - 2.0f);
	
	if (land2->getPositionX() <= 0)
	{
		land1->setPosition(Point::ZERO);
	}
	for (auto &singlePipe : pipes)
	{
		singlePipe->setPositionX(singlePipe->getPositionX() - 1.0f);
		if (singlePipe->getPositionX() < -PIPE_WIDTH/2)
		{
			singlePipe->setPositionX(visibleSize.width+PIPE_WIDTH/2);
			singlePipe->setPositionY(getRandomHeight());
			singlePipe->setName("newPipe");  //√ø¥Œ÷ÿ…Ë“ª∏˘π‹◊”£¨±ÍŒ™new
		}
	}
}

void GameScene::createPipes()
{
	//Õ¨∆¡ƒª≥ˆœ÷µƒ÷ª”–¡Ω∏˘π‹◊”£¨∑≈µΩ»›∆˜¿Ô√Ê£¨…œœ¬∞Û∂®Œ™“ª∏˘
	for (int i = 0; i < 2; i++)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Sprite *pipeUp = Sprite::createWithSpriteFrameName("pipe_up.png");
		Sprite *pipeDown = Sprite::createWithSpriteFrameName("pipe_down.png");
		Node *singlePipe = Node::create();
		//∏¯…œπ‹∞Û∂®∏’ÃÂ
		auto pipeUpBody = PhysicsBody::createBox(pipeUp->getContentSize());
		pipeUpBody->setDynamic(false);
		pipeUpBody->setContactTestBitmask(1);
		pipeUp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		pipeUp->setPhysicsBody(pipeUpBody);
		//∏¯¡Ω∏ˆπ‹◊”∑÷ø™…Ë÷√∏’ÃÂ£¨ø…“‘¡Ù≥ˆ÷–º‰µƒø’œ∂ πµ√–°ƒÒÕ®π˝
		//∏¯œ¬π‹∞Û∂®∏’ÃÂ
		auto pipeDownBody = PhysicsBody::createBox(pipeDown->getContentSize());
		pipeDownBody->setDynamic(false);
		pipeDownBody->setContactTestBitmask(1);
		pipeDown->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		pipeDown->setPhysicsBody(pipeDownBody);
		
		pipeUp->setPosition(0, PIPE_HEIGHT + PIPE_SPACE);
		singlePipe->addChild(pipeUp);
		singlePipe->addChild(pipeDown);  //pipeDownƒ¨»œº”µΩ£®0,0£©£¨…œœ¬∫œ≤¢£¨¥À ±singlePipe“‘œ¬√Êµƒπ‹◊”÷––ƒŒ™√™µ„
		singlePipe->setPosition(i*PIPE_INTERVAL + WAIT_DISTANCE, getRandomHeight() ); //…Ë÷√≥ı º∏ﬂ∂»
		singlePipe->setName("newPipe");
		this->addChild(singlePipe);  //∞—¡Ω∏ˆπ‹◊”∂ºº”»ÎµΩ≤„
		pipes.pushBack(singlePipe);  //¡Ω∏ˆπ‹◊”œ»∫ÛÃÌº”µΩ»›∆˜
	}
	
}

int GameScene::getRandomHeight()
{
	auto size = Director::getInstance()->getVisibleSize();
	// πµ√µ•∏˘π‹◊”◊›œÚ◊¯±Í‘⁄∆¡ƒª÷––ƒµ„-(40~270)÷–º‰ÀÊª˙≤®∂Ø,’‚∏ˆ «◊‘º∫ ‘≥ˆ¿¥µƒ
	return size.height / 2 - 40 - CCRANDOM_0_1() * (270 - 40);
}

void GameScene::update(float dt)
{
	//µ±”Œœ∑ø™ º ±£¨≈–∂œµ√∑÷£¨’‚∏ˆ∆‰ µ“≤ø…“‘–¥‘⁄∆‰À˚µÿ∑Ω£¨±»»Áπ‹◊”πˆ∂Øµƒ∏¸–¬∫Ø ˝¿Ô√ÊªÚ’ﬂ¥•√˛º‡≤‚¿Ô√Ê
	if (gameStatus == GAME_START)
	{
		for (auto &pipe : pipes)
		{
			if (pipe->getName() == "newPipe") //–¬¿¥“ª∏˘π‹◊”æÕ≈–∂œ
			{
				if (pipe->getPositionX() < birdSprite->getPositionX())
				{
//					score++;
//					scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
					SimpleAudioEngine::getInstance()->playEffect("point.mp3");
					pipe->setName("passed"); //±Íº«“—æ≠π˝µÙµƒπ‹◊”
				}
			}
		}
	}
	//–°ƒÒµƒ–˝◊™
	auto curVelocity = birdSprite->getPhysicsBody()->getVelocity();
	birdSprite->setRotation(-curVelocity.y*0.1 - 20);  //∏˘æ› ˙÷±∑ΩœÚµƒÀŸ∂»À„≥ˆ–˝◊™Ω«∂»£¨ƒÊ ±’ÎŒ™∏∫
	
	if (birdSprite->getPositionY() <= land1->getContentSize().height+BIRD_RADIUS)
	{
		birdSprite->stopAllActions(); //–°ƒÒπ“¡ÀæÕ≤ªƒ‹‘Ÿ…»≥·¡À
		birdSprite->setRotation(70);  //…Ë÷√Œ™◊Ï≥Øœ¬£¨À≥ ±’Î70∂»–˝◊™
		birdSprite->getPhysicsBody()->setDynamic(false);  //…Ë÷√Œ™≤ª∂Ø¡À
		SimpleAudioEngine::getInstance()->playEffect("die.mp3");
		this->unscheduleUpdate();  //‘⁄–°ƒÒµÙµΩµÿ√Ê…œ‘ŸÕ£÷πƒ¨»œ∏¸–¬
//		gamePanelAppear();  //µØ≥ˆº«∑÷≈∆
	}
	
}


bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	switch (gameStatus)
	{
		case GAME_OVER:
			break;
		case GAME_READY:
		{
			gameStart();
			birdSprite->getPhysicsBody()->setVelocity(Vec2(0, 250));
			SimpleAudioEngine::getInstance()->playEffect("wing.mp3");

			touchX = touch->getLocation().x;
		}
			break;
		case GAME_START:
		{
			auto curVelocity = birdSprite->getPhysicsBody()->getVelocity();
			birdSprite->getPhysicsBody()->setVelocity(Vec2(0, 250>(curVelocity.y + 500) ? (curVelocity.y + 500):250)); //œÚ…œµƒÀŸ∂» ‹œ¬Ωµ”∞œÏ
			SimpleAudioEngine::getInstance()->playEffect("wing.mp3");
			//ø™…œµ€ ”Ω«£¨¡Ù∏ˆ∫Û√≈£¨∫Ÿ∫Ÿ
			touchX = touch->getLocation().x;
		}
			break;
		default:
			break;
	}
	
	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	//µ±¥•√˛µ„ª¨∂Ø≥¨π˝100£¨∑÷ ˝À≤º‰’«100
	if (touch->getLocation().x - touchX > 100)
	{
//		score += 100;
//		scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		SimpleAudioEngine::getInstance()->playEffect("point.mp3");
	}
	
}

bool GameScene::onContactBegin(const PhysicsContact& contact)
{
	if (gameStatus == GAME_OVER)  //µ±”Œœ∑Ω· ¯∫Û≤ª‘Ÿº‡øÿ≈ˆ◊≤
		return false;
	
	gameOver();
	return true;
}

void GameScene::setPhysicWorld(PhysicsWorld *world)
{
	m_physicWorld = world;
}

///////////////////////////
void GameScene::gameStart()
{
	gameStatus = GAME_START;
//	score = 0;//÷ÿ÷√∑÷ ˝
//	scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
	this->getChildByName("logo")->setVisible(false); //logoœ˚ ß
//	scoreLabel->setVisible(true); //º∆∑÷ø™ º
	this->scheduleUpdate();//∆Ù∂Øƒ¨»œ∏¸–¬
	this->schedule(schedule_selector(GameScene::scrollLand), 0.01f); //∆Ù∂Øπ‹◊”∫Õµÿ∞Âπˆ∂Ø
	birdSprite->stopAction(swingAction); //”Œœ∑ø™ º∫ÛÕ£÷π…œœ¬∏°∂Ø
	birdSprite->getPhysicsBody()->setGravityEnable(true); //ø™ º ‹÷ÿ¡¶◊˜”√
}

void GameScene::gameOver()
{
	gameStatus = GAME_OVER;
	//ªÒ»°¿˙ ∑ ˝æ›
//	bestScore = UserDefault::getInstance()->getIntegerForKey("BEST");
//	if (score > bestScore)
//	{
//		bestScore = score;  //∏¸–¬◊Ó∫√∑÷ ˝
//		UserDefault::getInstance()->setIntegerForKey("BEST", bestScore);
//	}
	
	
	SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
	//”Œœ∑Ω· ¯∫ÛÕ£÷πµÿ∞Â∫Õπ‹µ¿µƒπˆ∂Ø
	this->unschedule(schedule_selector(GameScene::scrollLand));
	
	
}