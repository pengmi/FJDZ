#include "HelloWorldScene.h"
#include "GameScene.h"
#include "ScrollScene.h"
#include "ScrollButtonScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	srand((unsigned int)time(NULL));

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist","shoot.png");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));
	//
 //   // create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   this->addChild(menu, 1);
	///////////////////////////////////////
   

	/*auto playItem=MenuItemImage::create("btn-play-normal.png",
		"btn-play-select.png",
		CC_CALLBACK_1(HelloWorld::menuStartGameCallback,this));
	playItem->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/5));

	auto menu1=Menu::create(playItem,NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1,1);*/
	/////////////////////////////////////////////////

	auto sprite1 = Sprite::create("newBack.png");


    // position the sprite on the center of the screen
    sprite1->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	//sprite2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y+200));
	
	this->addChild(sprite1,0);
	//this->addChild(sprite2,10);

	//auto sprite3=Sprite::create("game_loading1.png");
	// this->addChild(sprite3,2);
	//sprite3->setPosition(origin.x+visibleSize.width/2-50,origin.y+visibleSize.height/2);
	//CCAnimation *animation=CCAnimation::create();
	//animation->addSpriteFrameWithFileName("game_loading1.png");
	//animation->addSpriteFrameWithFileName("game_loading2.png");
	//animation->addSpriteFrameWithFileName("game_loading3.png");
	//animation->addSpriteFrameWithFileName("game_loading4.png");
	//animation->setDelayPerUnit(5/4);
	//animation->setRestoreOriginalFrame(true);//是否回到初始帧

	//CCAnimate *action=CCAnimate::create(animation);
	//sprite3->runAction(CCRepeatForever::create(action));


	//////////scrollscene
	/*选择玩家的控件*/
	auto animation1 = Animation::create();
	animation1->addSpriteFrameWithFileName("ThunderNew/points002.png");
	animation1->addSpriteFrameWithFileName("ThunderNew/points003.png");
	animation1->addSpriteFrameWithFileName("ThunderNew/points001.png");
	animation1->setDelayPerUnit(0.8f);


	//auto scrollplayerlayer1 = ScrollScene::create();
	scrollplayerlayer1 = ScrollScene::create();
	//scrollplayerlayer1->setAnchorPoint(Vec2(0,0));
	//scrollplayerlayer1->ignoreAnchorPointForPosition(false);

	scrollplayerlayer1->setBackgroud(Sprite::create("ThunderNew/pilot-info-bg.png"),
		(Sprite::create("ThunderNew/points003.png")),animation1);//第一种（即选择飞机）
	scrollplayerlayer1->addNode(Sprite::create("ThunderNew/i-p-05d.png"));
	scrollplayerlayer1->addNode(Sprite::create("ThunderNew/i-p-02d.png"));
	scrollplayerlayer1->addNode(Sprite::create("ThunderNew/i-p-07d.png"));
	scrollplayerlayer1->setPosition(origin.x + visibleSize.width / 2, (origin.y + visibleSize.height / 5)*3);
	this->addChild(scrollplayerlayer1,5);

	/*选择关卡的控件*/
	auto animation2 = Animation::create();
	animation2->addSpriteFrameWithFileName("myPic/zijipdetupian-01.png");
	animation2->addSpriteFrameWithFileName("myPic/zijipdetupian-01.png");
	animation2->addSpriteFrameWithFileName("myPic/zijipdetupian-01.png");
	animation2->setDelayPerUnit(3.0f);

	//auto scrollplayerlayer2 = ScrollScene::create();
	scrollplayerlayer2 = ScrollScene::create();
	//scrollplayerlayer2->setAnchorPoint(Vec2(0, 0));
	//scrollplayerlayer2->ignoreAnchorPointForPosition(false);

	scrollplayerlayer2->setBackgroud(Sprite::create("ThunderNew/pilot-info-bg.png"),
		(Sprite::create("myPic/zijipdetupian-01.png")), animation2);//第二种（即选择关卡）
	scrollplayerlayer2->addNode(Sprite::create("myPic/noboundary.png"));
	scrollplayerlayer2->addNode(Sprite::create("myPic/baiyang-01.png"));
	scrollplayerlayer2->addNode(Sprite::create("myPic/juxie-01.png"));
	scrollplayerlayer2->addNode(Sprite::create("myPic/sheshou-01.png"));
	scrollplayerlayer2->setPosition(origin.x + visibleSize.width / 2, (origin.y + visibleSize.height / 5) * 2);

	this->addChild(scrollplayerlayer2, 5);

	/*选择操作的控件(button)*/


	auto startitem = MenuItemImage::create("myPic/begin_press_01.png",
		"myPic/begin_unpress_01.png",
		CC_CALLBACK_1(HelloWorld::menuStartGameCallback, this));
	auto startmenu = Menu::create(startitem, NULL);

	auto exititem = MenuItemImage::create("myPic/close-unpress-02.png",
		"myPic/close-press-02.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto exitmenu = Menu::create(exititem, NULL);

	startmenu->setPosition(origin.x + (visibleSize.width / 4)*1, (origin.y + visibleSize.height / 5) * 1);
	exitmenu->setPosition(origin.x + (visibleSize.width / 4) * 3, (origin.y + visibleSize.height / 5) * 1);

	this->addChild(startmenu);
	this->addChild(exitmenu);
	/*触摸监听*/
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	auto listener2 = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ScrollScene::onTouchBegan, scrollplayerlayer1);
	listener->onTouchMoved = CC_CALLBACK_2(ScrollScene::onTouchMoved, scrollplayerlayer1);
	listener->onTouchEnded = CC_CALLBACK_2(ScrollScene::onTouchEnded, scrollplayerlayer1);
	listener2->onTouchBegan = CC_CALLBACK_2(ScrollScene::onTouchBegan, scrollplayerlayer2);
	listener2->onTouchMoved = CC_CALLBACK_2(ScrollScene::onTouchMoved, scrollplayerlayer2);
	listener2->onTouchEnded = CC_CALLBACK_2(ScrollScene::onTouchEnded, scrollplayerlayer2);
	listener->setSwallowTouches(false);
	listener2->setSwallowTouches(false);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, scrollplayerlayer1);
	dispatcher->addEventListenerWithSceneGraphPriority(listener2, scrollplayerlayer2);
	this->setTouchEnabled(true);

	//explosion
	this->schedule(schedule_selector(HelloWorld::startExplosion), 1.0f);
	//this->scheduleOnce(schedule_selector(HelloWorld::startExplosion),0.1f);

	//file of scores
	loadScoresFile(0);

	//music preload
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/win01.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/gamebg0.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound/equip.mp3");
	//music play
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/gamebg0.mp3",true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7f);
    return true;
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuStartGameCallback(Ref *pSender)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.9f);
	SimpleAudioEngine::sharedEngine()->playEffect("sound/win01.mp3");
	auto director=Director::getInstance();

	if (scrollplayerlayer2->getCurPageNode()==CHAPTER_WUJIN)
	{
		Scene* pscene = WuJinGameScene::scene(scrollplayerlayer1->getCurPageNode());
		director->replaceScene(CCTransitionFade::create(3, pscene));
		/*Scene* pscene = GameScene::scene(scrollplayerlayer1->getCurPageNode());
		director->replaceScene(CCTransitionFade::create(3, pscene));*/
	}
	else if (scrollplayerlayer2->getCurPageNode() == CHAPTER_BAIYANG)
	{
		Scene* pscene = BaiYangGameScene::scene(scrollplayerlayer1->getCurPageNode());
		director->replaceScene(CCTransitionFade::create(3, pscene));
	}
	else if (scrollplayerlayer2->getCurPageNode() == CHAPTER_JUXIE)
	{
		Scene* pscene = JuXieGameScene::scene(scrollplayerlayer1->getCurPageNode());
		director->replaceScene(CCTransitionFade::create(3, pscene));
	}
	else
	{
		MessageBox("关卡未完成","");
	}
}

//读取分数文件
int HelloWorld::loadScoresFile(float dt)
{
	Size visiblesize = Director::getInstance()->getVisibleSize();

	int index = 0;
	char oneline[50];
	ifstream infile;
	infile.open("scoresfile/TopTenScores.txt", ios::in);
	if (!infile)
		return 0;
	while (!infile.eof()&&index<9)
	{
		infile.getline(oneline,50);
		
		Label* scoreLable = Label::create();
		scoreLable->setString(oneline);
		scoreLable->setBMFontFilePath("font/bitmapFontTest.fnt");
		scoreLable->setHorizontalAlignment(TextHAlignment::CENTER);
		scoreLable->setScale(0.5);
		scoreLable->setPosition(visiblesize.width / 2, visiblesize.height*0.9 - index * 50);
		this->addChild(scoreLable);
		index++;
	}
	return 1;
}
//开启效果
void HelloWorld::startExplosion(float dt)
{
	float scalerate = rand() % 2 * 0.1 + 0.1;
	Size visiablesize = Director::getInstance()->getVisibleSize();
	int xsize = visiablesize.width/3;
	int ysize = visiablesize.height/2;
	float xPos = rand()%xsize;
	float yPos = (rand()%ysize + ysize);
	//ParticleSystem* ps = ParticleExplosion::create();
	//ParticleSystem* ps = ParticleGalaxy::create();
	//ParticleSystem* ps = ParticleSun::create();
	//ParticleSystem* ps = ParticleFire::create();
	//ParticleSystem* m_ps = ParticleRain::create();;
	ParticleSystem *m_ps = ParticleMeteor::create();
	m_ps->setTexture(Director::getInstance()->getTextureCache()->addImage("explored.png"));

	m_ps->setEmissionRate(80.0f);
	m_ps->setScale(scalerate);
	m_ps->setPosition(Point(xPos, yPos));
	this->addChild(m_ps, 2);

	int speed = rand() % 3 + 5;

	CCMoveTo *psMoveTo = CCMoveTo::create(speed, ccp((rand()%(3*xsize)+(2*xsize)), -500));

	CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(HelloWorld::removeExplosion));

	CCSequence *seq = CCSequence::create(psMoveTo, actiondone, NULL);
	m_ps->runAction(seq);
}
void HelloWorld::removeExplosion(Node *psender) 
{
	ParticleSystem *m_ps = (ParticleSystem*)psender;
	this->removeChild(m_ps);
}