#include <PlayerLayer.h>

PlayerLayer *PlayerLayer::sharedPlane = NULL;

//创建玩家飞机层
PlayerLayer *PlayerLayer::create()
{
	PlayerLayer *pRet = new PlayerLayer;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

//玩家层初始化
bool PlayerLayer::init()
{
	bool bRet = false;
	do
	{
		if (Layer::init() == false)
			return false;

		this->CreatePlayerPlane();

		bRet = true;
	} while (0);
	return bRet;
}
//创建玩家飞机
void PlayerLayer::CreatePlayerPlane()
{

	CCSize visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto plane = GetPlayerPlaneSprite();
	//先将已经存在的移除
	this->removeChild(plane);
	//再创建玩家飞机
	plane = Sprite::create("ThunderNew/i-p-05d.png");
	Sprite* effectsprite = NULL;
	effectsprite = (Sprite*)(this->getChildByTag(PlaneEffectNum));
	auto blink = CCBlink::create(1, 3);
	if (effectsprite == NULL)
	{
		effectsprite = Sprite::create("ThunderNew/e-effect05 (2).png");
		this->addChild(effectsprite, PlaneLayerZOrder, PlaneEffectNum);
		effectsprite->setRotation(180.0f);
		effectsprite->runAction(CCRepeatForever::create(blink));
	}


	//plane->setScale(0.6f);
	plane->setOpacity(35);

	SetPlayerPlaneSprite(plane);



	GLubyte gb = plane->getOpacity();
	int gbint = gb;
	if (gb != 255)
	{
		this->schedule(schedule_selector(PlayerLayer::SetPlayerSpriteOpacity), 0.3);
	}

	plane->setPosition(origin.x + visibleSize.width / 2, origin.y + plane->getContentSize().height / 2);
	effectsprite->setPosition(origin.x + visibleSize.width / 2, origin.y);
	this->addChild(plane, PlaneLayerZOrder, PlaneNum);


	auto animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-05d.png");
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-05d.png");

	auto animate = CCAnimate::create(animation);
	plane->runAction(blink);
	plane->runAction(CCRepeatForever::create(animate));

}

//设置玩家的透明效果
void PlayerLayer::SetPlayerSpriteOpacity(float dt)
{
	int add = 20;
	Sprite * playerSprite = GetPlayerPlaneSprite();
	GLubyte gb = playerSprite->getOpacity();
	int gbint = gb;
	if (gbint<255)
		playerSprite->setOpacity(gbint + add);
	else
	{
		playerSprite->setOpacity(255);
		return;
	}
}
//播放玩家飞机爆炸动画
void PlayerLayer::AnimationPlayerPlane()
{

	Sprite *playerplanessprite = this->GetPlayerPlaneSprite();
	playerplanessprite->setOpacity(250);//设置透明度，变为无敌状态

	auto spriteframecache = HelpTool::GetFrameCache("explosion.plist", "explosion.png");
	SpriteFrame *frame[35];
	string tmpstr = "";
	string str = "";
	auto animation = CCAnimation::create();
	for (int i = 0; i < 35; i++)
	{
		CCString *num = CCString::createWithFormat("%d", i + 1);
		string numstr = num->_string.c_str();
		if (i<9)
		{
			tmpstr = "0" + numstr;
			str = "explosion_" + tmpstr + ".png";
		}
		else
		{
			tmpstr = "" + numstr;
			str = "explosion_" + tmpstr + ".png";
		}

		frame[i] = spriteframecache->getSpriteFrameByName(str);
		animation->addSpriteFrame(frame[i]);
	}

	animation->setDelayPerUnit(0.01f);

	auto* animate = CCAnimate::create(animation);
	CCFiniteTimeAction *actiondone = CCCallFunc::create(this,
		callfunc_selector(PlayerLayer::CreatePlayerPlane));
	playerplanessprite->runAction(Sequence::create(animate, actiondone, NULL));
}


/*当前飞机的创建*/
PlayerLayer * FirstPlayerLayer::create()
{
	PlayerLayer *pRet = new FirstPlayerLayer;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

void FirstPlayerLayer::CreatePlayerPlane()
{
	CCSize visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto plane = GetPlayerPlaneSprite();
	//先将已经存在的移除
	this->removeChild(plane);
	//再创建玩家飞机
	plane = Sprite::create("ThunderNew/i-p-05d.png");
	Sprite* effectsprite = NULL;
	effectsprite = (Sprite*)(this->getChildByTag(PlaneEffectNum));
	auto blink = CCBlink::create(1, 3);
	if (effectsprite == NULL)
	{
		effectsprite = Sprite::create("ThunderNew/e-effect05 (2).png");
		this->addChild(effectsprite, PlaneLayerZOrder, PlaneEffectNum);
		effectsprite->setRotation(180.0f);
		effectsprite->runAction(CCRepeatForever::create(blink));
	}


	//plane->setScale(0.6f);
	plane->setOpacity(35);

	SetPlayerPlaneSprite(plane);



	GLubyte gb = plane->getOpacity();
	int gbint = gb;
	if (gb != 255)
	{
		this->schedule(schedule_selector(PlayerLayer::SetPlayerSpriteOpacity), 0.3);
	}

	plane->setPosition(origin.x + visibleSize.width / 2, origin.y + plane->getContentSize().height / 2);
	effectsprite->setPosition(origin.x + visibleSize.width / 2, origin.y);
	this->addChild(plane, PlaneLayerZOrder, PlaneNum);


	auto animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-05d.png");
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-05d.png");

	auto animate = CCAnimate::create(animation);
	plane->runAction(blink);
	plane->runAction(CCRepeatForever::create(animate));
}

SecondPlayerLayer * SecondPlayerLayer::create()
{
	SecondPlayerLayer *pRet = new SecondPlayerLayer;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

void SecondPlayerLayer::CreatePlayerPlane()
{
	CCSize visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto plane = GetPlayerPlaneSprite();
	//先将已经存在的移除
	this->removeChild(plane);
	//再创建玩家飞机
	plane = Sprite::create("ThunderNew/i-p-02d.png");
	Sprite* effectsprite = NULL;
	effectsprite = (Sprite*)(this->getChildByTag(PlaneEffectNum));
	auto blink = CCBlink::create(1, 3);
	if (effectsprite == NULL)
	{
		effectsprite = Sprite::create("ThunderNew/e-effect05 (2).png");
		this->addChild(effectsprite, PlaneLayerZOrder, PlaneEffectNum);
		effectsprite->setRotation(180.0f);
		effectsprite->runAction(CCRepeatForever::create(blink));
	}


	//plane->setScale(0.6f);
	plane->setOpacity(35);

	SetPlayerPlaneSprite(plane);



	GLubyte gb = plane->getOpacity();
	int gbint = gb;
	if (gb != 255)
	{
		this->schedule(schedule_selector(PlayerLayer::SetPlayerSpriteOpacity), 0.3);
	}

	plane->setPosition(origin.x + visibleSize.width / 2, origin.y + plane->getContentSize().height / 2);
	effectsprite->setPosition(origin.x + visibleSize.width / 2, origin.y);
	this->addChild(plane, PlaneLayerZOrder, PlaneNum);


	auto animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-02d.png");
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-02d.png");

	auto animate = CCAnimate::create(animation);
	plane->runAction(blink);
	plane->runAction(CCRepeatForever::create(animate));
}

PlayerLayer * ThirdPlayerLayer::create()
{
	PlayerLayer *pRet = new ThirdPlayerLayer;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

void ThirdPlayerLayer::CreatePlayerPlane()
{
	CCSize visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto plane = GetPlayerPlaneSprite();
	//先将已经存在的移除
	this->removeChild(plane);
	//再创建玩家飞机
	plane = Sprite::create("ThunderNew/i-p-07d.png");
	Sprite* effectsprite = NULL;
	effectsprite = (Sprite*)(this->getChildByTag(PlaneEffectNum));
	auto blink = CCBlink::create(1, 3);
	if (effectsprite == NULL)
	{
		effectsprite = Sprite::create("ThunderNew/e-effect05 (2).png");
		this->addChild(effectsprite, PlaneLayerZOrder, PlaneEffectNum);
		effectsprite->setRotation(180.0f);
		effectsprite->runAction(CCRepeatForever::create(blink));
	}


	//plane->setScale(0.6f);
	plane->setOpacity(35);

	SetPlayerPlaneSprite(plane);



	GLubyte gb = plane->getOpacity();
	int gbint = gb;
	if (gb != 255)
	{
		this->schedule(schedule_selector(PlayerLayer::SetPlayerSpriteOpacity), 0.3);
	}

	plane->setPosition(origin.x + visibleSize.width / 2, origin.y + plane->getContentSize().height / 2);
	effectsprite->setPosition(origin.x + visibleSize.width / 2, origin.y);
	this->addChild(plane, PlaneLayerZOrder, PlaneNum);


	auto animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-07d.png");
	animation->addSpriteFrameWithFileName("ThunderNew/i-p-07d.png");

	auto animate = CCAnimate::create(animation);
	plane->runAction(blink);
	plane->runAction(CCRepeatForever::create(animate));
}
