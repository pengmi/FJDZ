#include "GameScene.h"
#include "PauseLayer.h"
#include "HelpTool.h"




int GameScene::FiniteScore=0;

GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}


//游戏界面初始化
bool GameScene::init(int playerselectednum)
{

	bool bRet=false;
	do
	{
		if(Layer::init()==false)
			break;

		this->setBackground();
		this->setLayer();
		//m_bk1=CCSprite::create("ThunderNew/bg_hei_0.jpg");
		//m_bk1->setAnchorPoint(Vec2(0,0));
		//m_bk1->setPosition(0,0);
		//this->addChild(m_bk1);
		//m_bk2=CCSprite::create("ThunderNew/bg_hei_0.jpg");
		//m_bk2->setAnchorPoint(Vec2(0,0));
		//m_bk2->setPosition(0,m_bk2->getContentSize().height);
		//this->addChild(m_bk2);
		//this->schedule(schedule_selector(GameScene::backgroundmove),0.01);
		
		//m_player=PlayerLayer::create();
		if ((playerselectednum)==FIRST_PLANE)
		{
			m_mybullet = FirstBulletLayer::create();
			m_player = FirstPlayerLayer::create();
		}
		else if ((playerselectednum) == SECOND_PLANE)
		{
			m_mybullet = SecondBulletLayer::create();
			m_player = SecondPlayerLayer::create();
		}
		else
		{
			m_mybullet = ThirdBulletLayer::create();
			m_player = ThirdPlayerLayer::create();
		}
		this->addChild(m_player);
		this->schedule(schedule_selector(GameScene::LaserMove),0.01);
		
		/*m_mybullet=BulletLayer::create();*/
		m_mybullet->StartShoot();
		this->addChild(m_mybullet, PlayerBulletLayerZOrder);


		/*EnemyLayer::m_BossSprite = NULL;
		m_enemy=EnemyLayer::create();
		m_enemy->StartEnemyPlane();
		m_enemy->StartBossMode();
		this->addChild(m_enemy,EnemyLayerZOrder);*/

		m_ufo=UFOLayer::create();
		//tmp
		m_ufo->AddZhaDanSprite(this);
		
		m_ufo->StartUFOMode();
		this->addChild(m_ufo);

		//m_bossBulletLayer = BossEnemyBulletLayer::create();
		//this->addChild(m_bossBulletLayer,BossBulletLayerZOrder);


		m_shutdown=false;
		m_score=0;
		m_diamondnum = 0;

		Size size=Director::getInstance()->getVisibleSize();
		Vec2 origin=Director::getInstance()->getVisibleOrigin();

		m_font=CCLabelBMFont::create("000","font/bitmapFontTest.fnt");
		m_font->setColor(ccc3(143,146,147));
		m_font->setAnchorPoint(ccp(0,0));
		m_font->setPosition(ccp(origin.x+100,origin.y+size.height-100));
		this->addChild(m_font,50);

		//按钮
		auto menuitem=MenuItemImage::create("game_pause_nor.png",
			"game_pause_pressed.png",
			CC_CALLBACK_1(GameScene::menuPauseCallBack,this));
		menuitem->setAnchorPoint(ccp(0,0));
		//menuitem->setPosition(origin.x,origin.y);
		menuitem->setPosition(size.width / 2-100, size.height/2 - 100);
		//menuitem->setPosition(ccp(origin.x + 100, origin.y + size.height - 100));
		auto menu=Menu::create(menuitem,NULL);
		this->addChild(menu,50);

		//进度条
		//auto process = ProgressFromTo::create(-1,0,100);
		////auto process = ProgressFromTo::create(10, 0, 100);
		//auto programeTimerSprite = Sprite::create("atomicBomb.png");
		//Size timerSpriteSize = programeTimerSprite->getContentSize();
		////auto programeTimerSprite = Sprite::create("lighling.png");
		//auto programeTimer = ProgressTimer::create(programeTimerSprite);
		//programeTimer->setPosition(timerSpriteSize.width/2,size.height/2);
		//programeTimer->setTag(TimerProgrameTag);
		//programeTimer->setScaleX(0.4);
		//programeTimer->setType(ProgressTimer::Type::BAR);
		//programeTimer->setMidpoint(Vec2(timerSpriteSize.width/2,0));

		//this->addChild(programeTimer);
		//programeTimer->runAction(process);

		//tmp
		
		//programeTimerSprite->setPosition(size.width/2,size.height/2);
		//auto animation = HelpTool::CreateAnimationByFile("pig.png",2,3);
		//animation->setDelayPerUnit(0.1);
		//this->addChild(programeTimerSprite);
		////animation->addSpriteFrameWithFileName("enemydespair.png");
		//auto animate = CCAnimate::create(animation);
		//animate->setOriginalTarget(false);
		////CCFiniteTimeAction *actiondone = CCCallFuncN::create(NULL);
		//programeTimerSprite->runAction(CCRepeatForever::create(animate));
		//programeTimerSprite->runAction(Sequence::create(animate, NULL, NULL));

		//创建钻石计数器
		auto diamondSprite = Sprite::create("ruby.png");
		Size diamondSpriteSize = diamondSprite->getContentSize();
		diamondSprite->setPosition(diamondSpriteSize.width / 2+50, size.height / 2);
		diamondSprite->setTag(DiamondTag);
		//diamondSprite->setScale(2.0f);
		//diamondSprite->setOpacity(0.7f);

		auto diamondCountLabel = Label::create();
		diamondCountLabel->setPosition(diamondSpriteSize.width / 2 + 80, size.height / 2);
		diamondCountLabel->setScale(0.5f);
		CCString *strscore = CCString::createWithFormat("%d", m_diamondnum);
		diamondCountLabel->setString(strscore->_string.c_str());
		//diamondCountLabel->setString();
		diamondCountLabel->setBMFontFilePath("font/bitmapFontTest.fnt");
		diamondCountLabel->setHorizontalAlignment(TextHAlignment::CENTER);
		diamondCountLabel->setTag(DiamondCounterTag);

		this->addChild(diamondCountLabel);
		this->addChild(diamondSprite);

		//////////
		this->scheduleUpdate();

		/////////////按钮
		setKeypadEnabled(true);
		////////////

		//触控
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
		listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
		listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
		//listener->onTouchCancelled = CC_CALLBACK_2(GameScene::keyBackClicked,this);
		listener->setSwallowTouches(true);
		dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
		this->setTouchEnabled(true);

		srand((unsigned)time(NULL));

		//SimpleAudioEngine::sharedEngine()->preloadEffect("sound/bullet.mp3"); 
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/game_music.mp3");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_bomb.mp3");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_double_laser.mp3");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/bosswaring.mp3");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/click.mp3");
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/upgrade1.mp3");
		
		//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.9f);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
		
		//SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);

		bRet=true;
	}while(0);
	return bRet;
}

//暂停（实际是停止）
void GameScene::menuPauseCallBack(Ref *psender)
{
	auto director=Director::getInstance();
	Scene* pscene=PauseLayer::scene();
	director->replaceScene(CCTransitionFade::create(3,pscene));

}

void GameScene::setBackground()
{
	m_bk1 = CCSprite::create("ThunderNew/bg_hei_0.jpg");
	m_bk1->setAnchorPoint(Vec2(0, 0));
	m_bk1->setPosition(0, 0);
	this->addChild(m_bk1);
	m_bk2 = CCSprite::create("ThunderNew/bg_hei_0.jpg");
	m_bk2->setAnchorPoint(Vec2(0, 0));
	m_bk2->setPosition(0, m_bk2->getContentSize().height);
	this->addChild(m_bk2);
	this->schedule(schedule_selector(GameScene::backgroundmove), 0.01);
}

void GameScene::setLayer()
{
	EnemyLayer::m_BossSprite = NULL;
	m_enemy = EnemyLayer::create();
	m_enemy->StartEnemyPlane();
	m_enemy->StartBossMode();
	this->addChild(m_enemy, EnemyLayerZOrder);


	m_bossBulletLayer = BossEnemyBulletLayer::create();
	this->addChild(m_bossBulletLayer,BossBulletLayerZOrder);
}

//背景移动
void GameScene::backgroundmove(float dt)
{

	//int speed = rand() % 9 + 2;
	int speed = 4;

	m_bk1->setPositionY(m_bk1->getPositionY()-speed);
	m_bk2->setPositionY(m_bk2->getPositionY()-speed);
	if(m_bk2->getPositionY()<=0){
		m_bk1->setPositionY(0);
		m_bk2->setPositionY(m_bk2->getContentSize().height);
	}
}

//sp[1]是排前面的，所以sp[1]到了最终位置以后就回到原位
void GameScene::LaserMove(float dt)
{
	auto player = m_player->SharePlane()->getChildByTag(PlaneNum);
	auto playerpoint = player->getPosition();
	auto contentsize = Director::getInstance()->getVisibleSize();
	auto playerrect = player->getBoundingBox();
	Sprite* sp1[2] = {NULL};

	sp1[0] = (Sprite*)(this->getChildByTag(PlayerLaserMainTag + 0));
	sp1[1] = (Sprite*)(this->getChildByTag(PlayerLaserMainTag + 1));

	if (sp1[1] != NULL&&sp1[0]!=NULL)
	{
		sp1[0]->setPosition(playerpoint.x,sp1[0]->getPositionY()+10);
		sp1[0]->setScaleX((float)(sp1[0]->getScaleX()) - 0.004);

		sp1[1]->setPosition(playerpoint.x, sp1[1]->getPositionY() + 10);
		sp1[1]->setScaleX((float)(sp1[1]->getScaleX()) - 0.004);

		if (sp1[1]->getPositionY()>int((contentsize.height+ contentsize.height /2)))
		{
			sp1[1]->setPosition(playerpoint.x,
				contentsize.height / 2);
			
			sp1[0]->setPosition(playerpoint.x,
				-contentsize.height / 2);
		}
	}

}

int GameScene::GetPlayerSelected()
{
	return PLAYER_SELECTED;
}




bool GameScene::onTouchBegan(Touch *touch,Event *user_event)
{
	Point beginPoint=touch->getLocationInView();   
    beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint); //获取触摸坐标
	Rect rectplayer=this->m_player->boundingBox();
	Rect touchrect;
	touchrect.origin.x=beginPoint.x;
	touchrect.origin.y=beginPoint.y;
	touchrect.size.width=30;
	touchrect.size.height=30;
	if(rectplayer.intersectsRect(touchrect)){
		m_shutdown=true;
	}
	////////////
	
	auto player = (Sprite*)( m_player->SharePlane()->getChildByTag(PlaneNum));

	auto playerposition = player->getPosition();

	Rect playerrect = HelpTool::GetSpritePosition(player);

	auto contentsize = Director::getInstance()->getVisibleSize();
	auto sprite = (Sprite*)(this->getChildByTag(ZhaDanTag));
	if (sprite!=NULL)//判断是否有激光可用
	{
		Rect spriterect = HelpTool::GetSpritePosition(sprite);
		if (touchrect.intersectsRect(spriterect))
		{
			auto textTure = Director::getInstance()->getTextureCache()->
				addImage("ThunderNew/laser-01d.png");
			SpriteFrame* framearr1[2];
			Sprite* sp1[2];
			float texttureheight = 540;
			float textturewidth = 135;
			for (int i=0; i<2; i++)
			{
				framearr1[i] = SpriteFrame::createWithTexture(textTure, 
					Rect(textturewidth * 1, texttureheight * 0+90, textturewidth, texttureheight-140));
				sp1[i] = Sprite::createWithSpriteFrame(framearr1[0]);//用第一帧精灵对象，初始化精灵
				sp1[i]->setPosition(Vec2(playerposition.x + playerrect.size.width / 2,
					contentsize.height*i-contentsize.height /2));

				float scaley = contentsize.height/(sp1[i]->getBoundingBox().size.height);
				sp1[i]->setScaleX(1.0f);
				sp1[i]->setScaleY(scaley);

				addChild(sp1[i], LaserLayerZOrder, (PlayerLaserMainTag + i));

			}
			
			this->scheduleOnce(schedule_selector(GameScene::removePlayerLaser),5.0f);

			this->removeChild(sprite);
		}
	}
	
	return true;
}

void GameScene::onTouchMoved(Touch *touch,Event *user_event)
{
	if(m_shutdown==true){
		auto effect = (Sprite*)(m_player->SharePlane()->getChildByTag(PlaneEffectNum));
		Vec2 newpos=this->m_player->getChildByTag(PlaneNum)->getPosition()+touch->getDelta();
		Size visiblesize=Director::getInstance()->getVisibleSize();
		Vec2 origin=Director::getInstance()->getVisibleOrigin();
		//Size planesize=this->m_player->getChildByTag(PlaneNum)->getContentSize();
		Size planesize = this->m_player->getChildByTag(PlaneNum)->getContentSize();
		planesize.width = planesize.width*0.15;
		planesize.height = planesize.height*0.15;

		if(newpos.x<origin.x){
			newpos.x=planesize.width/2+origin.x;
		}
		if(newpos.x>origin.x+visiblesize.width){
			newpos.x=origin.x+visiblesize.width-planesize.width/2;
		}
		if(newpos.y<origin.y){
			newpos.y=planesize.height/2+origin.y;
		}
		if(newpos.y>origin.y+visiblesize.height){
			newpos.y=origin.y+visiblesize.height-planesize.height/2;
		}
		PlayerLayer::SharePlane()->getChildByTag(PlaneNum)->setPosition(newpos);
		
		effect->setPosition(newpos.x,newpos.y-(planesize.height*(1/0.15))/2);

	}
}

void GameScene::onTouchEnded(Touch *touch,Event *user_event)
{
	m_shutdown=false;
}

void GameScene::keyBackClicked(Touch * touch, Event * user_evenr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::keyMenuClicked(Touch * touch, Event * user_evenr)
{
	
}

//飞机处理动画（血量为0，播放）并移除sprite
void GameScene::AnimationPlane(Sprite *sprite)
{
	int tag = sprite->getTag();

	startDestroyedMode(sprite);

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
	CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(GameScene::removePlane));
	
	/////////////////////////////////////////////////
	int score=0;
	if(tag==LittlePlane){
		
		score=LittlePlaneScore;
	}
	else if(tag==BigPlane){
		
		score=BigPlaneScore;
	}
	else if(tag==MorePlane){
		
		score=MoreBigPlaneScore;
	}
	else if (tag == Bomb) {
		
		score = BombScore;
	}
	else if (tag==Pig)
	{
		score = PigScore;
	}
	else if(tag == Missile)
	{
		score = MissileScore;
		actiondone = CCCallFuncN::create(this,
			callfuncN_selector(GameScene::removeMissile));
	}
	else if (tag == JuXieStarsTag)
	{
		score = JuXieStarsScore;
		actiondone = CCCallFuncN::create(this,
			callfuncN_selector(GameScene::removeMissile));
	}
	sprite->runAction(Sequence::create(animate, actiondone, NULL));
	m_score+=score;
	CCString *strscore=CCString::createWithFormat("%d",m_score);
	m_font->setString(strscore->_string.c_str());
	FiniteScore=m_score;
}
//移除钻石
void GameScene::removeDiamond(Node * psender)
{
	this->removeChild((Sprite*)psender);
}

//移除飞机
void GameScene::removePlane(Node *pSender)
{
	this->m_enemy->removeChild(dynamic_cast<Sprite*>(pSender));
}
void GameScene::removeMissile(Node *pSender)
{
	this->m_bossBulletLayer->removeChild(dynamic_cast<Sprite*>(pSender));
}


void GameScene::removeUfo(Node * pSender)
{
	this->m_ufo->removeChild(dynamic_cast<Sprite*>(pSender));
}

void GameScene::removeBullet(Node * pSender)
{

	this->m_mybullet->removeChild(dynamic_cast<Sprite*>(pSender));

}

void GameScene::removeBoss(Node * pSender)
{
	this->m_enemy->removeChild((Sprite*)pSender);
	EnemyLayer::m_BossSprite = NULL;
}

void GameScene::removePlayerLaser(float dt)
{
	auto sp0 = this->getChildByTag(PlayerLaserMainTag);
	auto sp1 = this->getChildByTag(PlayerLaserMainTag+1);
	this->removeChild((Sprite*)sp0);
	this->removeChild((Sprite*)sp1);
}

//判断Boos是否击中玩家
int GameScene::IfBossBulletintersects()
{
	auto playerSprite = (Sprite*)
		(PlayerLayer::SharePlane()->getChildByTag(PlaneNum));//根据PlaneNum找到玩家飞机

	GLubyte gb = playerSprite->getOpacity();
	int gbint = gb;
	if (gbint<255)
	{
		return 0;
	}

	Rect PlayerRect = HelpTool::GetSpritePosition(playerSprite);
	for (vector<Sprite*>::iterator it = m_bossBulletLayer->m_bossbullet.begin()
		; it != m_bossBulletLayer->m_bossbullet.end();)
	{
		Rect bulletRect = HelpTool::GetSpritePosition(*it) ;
		if (bulletRect.intersectsRect(PlayerRect))
		{
			this->m_bossBulletLayer->removeChild(*it);
			it=m_bossBulletLayer->m_bossbullet.erase(it);

			return 1;
		}
		else
			it++;
		
	}
	return 0;
}
//操作玩家生命值
void GameScene::PlayerLifeCount()
{
	typedef vector<UFOLayer::lifenode>::iterator lifIter;//道具迭代器
	//操作玩家血量,操作ufo图标
	//当还有生命的时候（>=1）
	if (m_ufo->total_lifenumber>0 && (m_ufo->m_lifearry.begin() != m_ufo->m_lifearry.end()))
	{
		/*char a[11];
		const char* p = itoa(m_ufo->total_lifenumber,a,10);
		MessageBox(p,"title");*/

		m_ufo->total_lifenumber--;
		m_mybullet->m_secondbullet = false;
		m_mybullet->m_bulletNum = 0;
		//	UFOLayer::m_isshuangzidan = false;//玩家飞机死亡后变为单子弹
		//	UFOLayer::m_islifenumber = false;					
		//	UFOLayer::m_iszhadan = false;

		/*p = itoa(m_ufo->total_lifenumber, a, 10);
		MessageBox(p, "title");*/

		lifIter lif = m_ufo->m_lifearry.begin();

		removeChild(lif->sprite);
		lif = m_ufo->m_lifearry.erase(lif);
	}
	else
	{
		menuPauseCallBack(this);
	}
}

//敌机被击中的处理
void GameScene::AnimationHitPlane(Sprite* sprite)
{
	int tag = sprite->getTag();
	
	startHitExplosionAnimation(sprite);

	if(tag==BigPlane){
		auto animation=CCAnimation::create();
		animation->setDelayPerUnit(0.1);
		animation->setRestoreOriginalFrame(true);
		animation->addSpriteFrameWithFileName("ThunderNew/c-03.png");
		auto animate=CCAnimate::create(animation);
		sprite->runAction(animate);
	}
	else if(tag==MorePlane){
		auto animation=CCAnimation::create();
		animation->setDelayPerUnit(0.1);
		animation->setRestoreOriginalFrame(true);
		animation->addSpriteFrameWithFileName("ThunderNew/c-05.png");
		auto animate=CCAnimate::create(animation);
		sprite->runAction(animate);
	}

}
//boss击中动画
void GameScene::AnimationHitBoss(Sprite * pSender,int num)
{
	//SimpleAudioEngine::sharedEngine()->playEffect("sound/click.mp3");
	auto sprite = (Sprite*)pSender;
	sprite->setScale(0.9f);
	startHitExplosionAnimation(sprite);

	Point point=sprite->getPosition();
	auto animation = HelpTool::GetHitAnimationByFileName("wsparticle_p01.plist", "wsparticle_p01.png",num);
	animation->setDelayPerUnit(0.03f);
	animation->setRestoreOriginalFrame(true);
	auto* animate = CCAnimate::create(animation);
	//auto moveto = CCMoveTo::create(0.001,point);
	CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(GameScene::removeBullet));
	sprite->runAction(Sequence::create(animate, actiondone, NULL));
	//sprite->runAction(animate);
	//playerplanessprite->runAction(animate);
}

void GameScene::AnimationDestroyBoss(Sprite * sprite)
{
	float xPos = sprite->getPositionX();
	float yPos = sprite->getPositionY();
	ParticleSystem* ps = ParticleExplosion::create();
	//ParticleSystem* ps = ParticleGalaxy::create();
	//ParticleSystem* ps = ParticleSun::create();
	//ParticleSystem* ps = ParticleFire::create();
	//ParticleSystem* ps = ParticleRain::create();;
	//ParticleSystem *ps = ParticleMeteor::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("explored.png"));

	ps->setEmissionRate(360.0f);
//	ps->setScale(1.0f);
	//ps->setDuration(0.05f);
	ps->setPosition(Point(xPos, yPos));
	this->addChild(ps,BossBulletLayerZOrder);

	auto animation = HelpTool::GetHitAnimationByFileName("wsparticle_p01.plist", "wsparticle_p01.png", 4);
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(false);
	auto* animate = CCAnimate::create(animation);
	auto animateaction = CCRepeatForever::create(animate);
	sprite->runAction(animateaction);

	CCMoveTo *psMoveTo1 = CCMoveTo::create(0.05, ccp(xPos + 10, yPos));
	CCMoveTo *psMoveTo2 = CCMoveTo::create(0.05, ccp(xPos + 10, yPos + 10));
	CCMoveTo *psMoveTo3 = CCMoveTo::create(0.05, ccp(xPos , yPos + 10));
	CCMoveTo *psMoveTo4 = CCMoveTo::create(0.05, ccp(xPos - 10, yPos + 10));
	CCMoveTo *psMoveTo5 = CCMoveTo::create(0.05, ccp(xPos , yPos + 10));
	CCMoveTo *psMoveTo6 = CCMoveTo::create(0.05, ccp(xPos + 10, yPos));
	CCMoveTo *psMoveTo7 = CCMoveTo::create(0.05, ccp(xPos + 10, yPos + 10));
	CCMoveTo *psMoveTo8 = CCMoveTo::create(0.05, ccp(xPos, yPos + 10));
	CCMoveTo *psMoveTo9 = CCMoveTo::create(0.05, ccp(xPos - 10, yPos + 10));
	CCMoveTo *psMoveTo10 = CCMoveTo::create(0.05, ccp(xPos, yPos + 10));
	CCSequence *moveseq = CCSequence::create(
		psMoveTo1, psMoveTo2, psMoveTo3, psMoveTo4, psMoveTo5, 
		psMoveTo6, psMoveTo7, psMoveTo8, psMoveTo9, psMoveTo10,
		NULL);
	auto spawn = CCSpawn::create(moveseq,NULL);
	CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(GameScene::removeBoss));

	CCSequence *seq = CCSequence::create(spawn, actiondone, NULL);
	sprite->runAction(seq);
}

//敌机被攻击的粒子特效
void GameScene::startHitExplosionAnimation(Sprite *sprite)
{
	float xPos= sprite->getPositionX();
	float yPos = sprite->getPositionY();
	//ParticleSystem* ps = ParticleExplosion::create();
	//ParticleSystem* ps = ParticleGalaxy::create();
	//ParticleSystem* ps = ParticleSun::create();
	ParticleSystem* ps = ParticleFire::create();
	//ParticleSystem* ps = ParticleRain::create();;
	//ParticleSystem *ps = ParticleMeteor::create();
	//ps->setTexture(Director::getInstance()->getTextureCache()->addImage("explored.png"));

	ps->setEmissionRate(80.0f);
	ps->setScale(0.2f);
	ps->setDuration(0.05f);
	ps->setPosition(Point(xPos, yPos));
	this->addChild(ps, 10);
	CCMoveTo *psMoveTo = CCMoveTo::create(1, ccp(xPos+50,yPos+50));
	CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(GameScene::removeExplosionAnimation));

	CCSequence *seq = CCSequence::create(psMoveTo, actiondone, NULL);
	ps->runAction(seq);
}
//敌机爆炸以后生成钻石
void GameScene::startDestroyedMode(Node *pSender)
{
	Sprite *enemySprite = (Sprite*)pSender;
	CCPoint enemySpritePosition = enemySprite->getPosition();

	int randDiamond= rand() % 5;
	for (int i = 0; i < randDiamond; i++)
	{
		Sprite* sprite = Sprite::create("diamond.png");

		float xPos = enemySpritePosition.x+ rand() % 3 * 10;
		float yPos = enemySpritePosition.y + rand() % 3 * 10;
		float endxPos = xPos + rand() % 4 * 30 - 60;
		float endyPos = yPos + rand() % 4 * 30 - 60;

		//将钻石放进数组里，以便操作
		diamondNode dn;
		dn.sprite = sprite;
		m_diamondArray.push_back(dn);

		sprite->setPosition(xPos,yPos);
		this->addChild(sprite);
		auto animation = CCAnimation::create();
		animation->addSpriteFrameWithFile("diamond.png");
		animation->addSpriteFrameWithFile("ruby.png");
		animation->addSpriteFrameWithFile("diamond_blue.png");
		animation->addSpriteFrameWithFile("diamond_gold.png");
		animation->addSpriteFrameWithFile("diamond_green.png");
		animation->setDelayPerUnit(0.1);
		animation->setRestoreOriginalFrame(true);
		animation->setLoops(-1);
		auto animate = CCAnimate::create(animation);

		sprite->runAction(RepeatForever::create(animate));
		//CCMoveTo *diamondMoveTo = CCMoveTo::create(3,ccp(xPos,-10));

		CCMoveTo *diamondMoveTo = CCMoveTo::create(0.5, ccp(endxPos, endyPos));
		CCSequence *seq = CCSequence::create(diamondMoveTo, CCCallFuncN::create(this,
			callfuncN_selector(GameScene::diamondFall)), NULL);

		sprite->runAction(seq);
	}	
}
//钻石下落
void GameScene::diamondFall(Node * pSender)
{
	auto diamondSprite = (Sprite*)pSender;
	CCPoint diamondSpritePosition = diamondSprite->getPosition();
	float xPos = diamondSpritePosition.x ;
	float yPos = diamondSpritePosition.y ;

	Rect diamondRect = HelpTool::GetSpritePosition(diamondSprite);

	auto playerSprite = (Sprite*)
		(PlayerLayer::SharePlane()->getChildByTag(PlaneNum));//根据PlaneNum找到玩家飞机
	Rect PlayerRect = HelpTool::GetSpritePosition(playerSprite);
	CCPoint playerPoint = CCPoint(PlayerRect.origin.x,PlayerRect.origin.y);

	CCMoveTo *diamondMoveTo;
	CCSequence *seq;
	if (yPos<=0)
	{
		diamondMoveTo = CCMoveTo::create(3, ccp(xPos, yPos - 50));
		seq = CCSequence::create(diamondMoveTo, CCCallFuncN::create(this,
			callfuncN_selector(GameScene::removeDiamond)), NULL);
	}
	else
	{
		if (diamondRect.intersectsCircle(playerPoint, (PlayerRect.size.width + 100)))
		{
			diamondMoveTo = CCMoveTo::create(0.3, playerPoint);
			seq = CCSequence::create(diamondMoveTo, CCCallFuncN::create(this,
				callfuncN_selector(GameScene::removeDiamond)), NULL);

			auto diamondLable = (Label*)(this->getChildByTag(DiamondCounterTag));
			m_diamondnum++;
			CCString *strscore = CCString::createWithFormat("%d", m_diamondnum);
			diamondLable->setString(strscore->_string.c_str());
			
		}
		else
		{
			diamondMoveTo = CCMoveTo::create(0.3f, ccp(xPos, yPos - 40));
			seq = CCSequence::create(diamondMoveTo, CCCallFuncN::create(this,
				callfuncN_selector(GameScene::diamondFall)), NULL);
		}	
	}


	//CCMoveTo *diamondMoveTo = CCMoveTo::create(3, ccp(xPos, yPos-50));
	/*CCSequence *seq = CCSequence::create(diamondMoveTo, CCCallFuncN::create(this,
		callfuncN_selector(GameScene::removeDiamond)), NULL);*/

	diamondSprite->runAction(seq);
}
//移除粒子特效
void GameScene::removeExplosionAnimation(Node *psender)
{
	ParticleSystem *m_ps = (ParticleSystem*)psender;
	this->removeChild(m_ps);
}


//刷新   

void GameScene::update(float dt)
{
	//判断boss是否出现
	auto bosssprite = EnemyLayer::ShareBoss();
	Rect bossrect;
	if (bosssprite)
	{
		 bossrect= HelpTool::GetSpritePosition(bosssprite);
	}

	//typedef vector<UFOLayer::lifenode>::iterator lifIter;//道具迭代器
	typedef vector<EnemyLayer::node>::iterator Iter;//敌机迭代器
	typedef vector<BossEnemyBulletLayer::node>::iterator missileIter;//敌机迭代器
	Rect rect2 = HelpTool::GetSpritePosition((Sprite*)(PlayerLayer::SharePlane()->getChildByTag(PlaneNum)));//根据PlaneNum找到玩家飞机
	bool del=false;


	//检测道具和玩家飞机的碰撞
	if(m_ufo->isdaojuexit()){
		Rect rect1= HelpTool::GetSpritePosition(this->m_ufo->m_daoju);
		//根据PlaneNum找到玩家飞机
		//Rect rect2=GetSpritePosition((Sprite*)(PlayerLayer::SharePlane()->getChildByTag(PlaneNum)));
		if(rect1.intersectsRect(rect2)){
			if(UFOLayer::m_ufotype==ZhaDan){
				SimpleAudioEngine::sharedEngine()->playEffect("sound/get_bomb.mp3");
				
				m_ufo->AddZhaDanSprite(this);
				m_ufo->PengzhuangRemoveDaoju();
				//this->m_mybullet->m_secondbullet=false;
				//this->m_mybullet->m_firstbullet=true;
			}
			else if(UFOLayer::m_ufotype == ShuangZidan){
				SimpleAudioEngine::sharedEngine()->playEffect("sound/get_double_laser.mp3");
				m_ufo->PengzhuangRemoveDaoju();
				this->m_mybullet->m_secondbullet=true;
				if (this->m_mybullet->m_bulletNum<2)
				{
					this->m_mybullet->m_bulletNum++;
				}
				//this->m_mybullet->m_firstbullet=false;
			}
			else if (UFOLayer::m_ufotype == Life)
			{
				SimpleAudioEngine::sharedEngine()->playEffect("sound/upgrade1.mp3");
				m_ufo->AddLifeSprite(this);
				m_ufo->PengzhuangRemoveDaoju();
			}
			else
				;
		}
	}
	//找到激光
	auto sp0 = this->getChildByTag(PlayerLaserMainTag);
	auto sp1 = this->getChildByTag(PlayerLaserMainTag + 1);
	Rect sp0Rect;
	Rect sp1Rect;
	if (sp0 != NULL&&sp1 != NULL)
	{
		sp0Rect = HelpTool::GetSpritePosition((Sprite*)sp0);
		sp1Rect = HelpTool::GetSpritePosition((Sprite*)sp1);
	}
	//双重循环，检测子弹\玩家与敌机是否碰撞，碰撞则处理飞机
	for(vector<Sprite*>::iterator it1=m_mybullet->m_bullet.begin()
		;it1!=m_mybullet->m_bullet.end();)
	{
		Rect it1rect = HelpTool::GetSpritePosition(*it1);//子弹 
		
		//检测敌机和子弹(激光)\玩家飞机相撞
		for(Iter it2=this->m_enemy->m_enemyarray.begin();it2!=m_enemy->m_enemyarray.end();)
		{
			Rect it2rect = HelpTool::GetSpritePosition(it2->sprite);//敌机
			//////////////////////////////////////////////////////激光与敌机碰撞

			if (sp0 != NULL&&sp1 != NULL)
			{
				if (it2rect.intersectsRect(sp0Rect) || it2rect.intersectsRect(sp1Rect))
				{
					it2->life=(it2->life-2);
					if (it2->life<=0)
					{
						AnimationPlane(it2->sprite);
						it2 = this->m_enemy->m_enemyarray.erase(it2);
						if (it2==m_enemy->m_enemyarray.end())
						{
							break;
						}
					}
				}
			}
			
			////////////////////////////////////////////////////////

			
			if(it1rect.intersectsRect(it2rect)&&!(it2rect.intersectsRect(rect2)))
			{
				it2->life--;

				//当飞机血量为0时，播放飞机爆炸动画
				if(it2->life<=0)
				{
					AnimationPlane(it2->sprite);
					it2=this->m_enemy->m_enemyarray.erase(it2);
				}
				else if(it2->life>0){
					AnimationHitPlane(it2->sprite);
					++it2;
				}
			}
			else if (it2rect.intersectsRect(rect2))
			{

				it2->life == 0;
				AnimationPlane(it2->sprite);
				it2 = this->m_enemy->m_enemyarray.erase(it2);

				//删除现在玩家飞机精灵，重新生成
				auto playersprite= m_player->GetPlayerPlaneSprite();
				GLubyte gb = playersprite->getOpacity();
				int gbint = gb;
				if (gbint<255)//透明度小于255说明飞机刚刚生成，不能被攻击
				{
					break;
				}
				//播放玩家飞机坠毁动画 
				m_player->AnimationPlayerPlane();
				
				PlayerLifeCount();
			}
			else
				++it2;
		}
		//////////////////////////子弹与boss导弹

		for (missileIter it = m_bossBulletLayer->m_bossmissilearry.begin(); 
			it !=m_bossBulletLayer->m_bossmissilearry.end();)
		{
			Rect missileRect = HelpTool::GetSpritePosition(it->sprite);
			if (missileRect.intersectsRect(rect2)||missileRect.intersectsRect(it1rect))
			{
				if (missileRect.intersectsRect(it1rect))
				{
					it->life--;
					///////////////////////////////////////
					//AnimationHitBoss(*it1,2);
					AnimationHitPlane(it->sprite);
					//it1 = this->m_mybullet->m_bullet.erase(it1);
					//////////////////////////////////////////	
				}
				else
				{
				}

				if (missileRect.intersectsRect(rect2))
				{
					it->life = 0;
				}
				if (it->life<=0)
				{
					AnimationPlane(it->sprite);
					it = m_bossBulletLayer->m_bossmissilearry.erase(it);
				}
				else
				{
					it++;//导弹向前查询
				}
				
			}
			else
			{
				it++;//导弹向前查询
			}
		}

		/////////////////子弹与boss
		if (bosssprite&&EnemyLayer::m_BossTotalLife>0)
		{

			if (it1rect.intersectsRect(bossrect))
			{
				EnemyLayer::m_BossTotalLife--;
				//////////////////////////////
				if (it1 == m_mybullet->m_bullet.end())
				{
					break;//直接退出
				}
				
				////////////////////////////////
				AnimationHitBoss(*it1, 1);
				it1 = this->m_mybullet->m_bullet.erase(it1);
				if (EnemyLayer::m_BossTotalLife <= 0)
				{
					AnimationDestroyBoss(bosssprite);
					/*MessageBox("bossdie", "");*/
				}
			}
			else
			{
				if (it1 == m_mybullet->m_bullet.end())
				{
					break;//直接退出
				}
				else
				{
					++it1;
				}
				/////////////////////////////////////////////////
				//++it1;
			}
			
		}
		else
		{
			////////////////////////////////////////
			if (it1 == m_mybullet->m_bullet.end())
			{
				break;//直接退出
			}
			else
			{
				++it1;
			}
			////////////////////////////////////////
		//	++it1;
		}
		////////////////

	}
	



	//如果有Boss开始发射子弹，判断boss
	if (bosssprite)
	{
		m_bossBulletLayer->StartBossShoot();
		//Boss是否击中玩家
		if (IfBossBulletintersects())
		{
			//播放玩家飞机坠毁动画 
			m_player->AnimationPlayerPlane();
		}
		if (sp0 != NULL&&sp1 != NULL)
		{
			if (sp0Rect.intersectsRect(bossrect)||
				sp1Rect.intersectsRect(bossrect))
			{
				EnemyLayer::m_BossTotalLife--;

				if (EnemyLayer::m_BossTotalLife <= 0)
				{
					AnimationDestroyBoss(bosssprite);
				}
			}

		}
	}

}

void WuJinGameScene::setBackground()
{
	m_bk1 = CCSprite::create("ThunderNew/bg_hei_0.jpg");
	m_bk1->setAnchorPoint(Vec2(0, 0));
	m_bk1->setPosition(0, 0);
	this->addChild(m_bk1);
	m_bk2 = CCSprite::create("ThunderNew/bg_hei_0.jpg");
	m_bk2->setAnchorPoint(Vec2(0, 0));
	m_bk2->setPosition(0, m_bk2->getContentSize().height);
	this->addChild(m_bk2);
	this->schedule(schedule_selector(GameScene::backgroundmove), 0.01);
}

void WuJinGameScene::setLayer()
{
	EnemyLayer::m_BossSprite = NULL;
	m_enemy = WuJinSceneEnemyLayer::create();
	m_enemy->StartEnemyPlane();
	m_enemy->StartBossMode();
	this->addChild(m_enemy, EnemyLayerZOrder);


	m_bossBulletLayer = BossEnemyBulletLayer::create();
	this->addChild(m_bossBulletLayer,BossBulletLayerZOrder);
}


void BaiYangGameScene::setBackground()
{
	m_bk1 = CCSprite::create("myPic/img_bg_5.jpg");
	m_bk1->setAnchorPoint(Vec2(0, 0));
	m_bk1->setPosition(0, 0);
	this->addChild(m_bk1);
	m_bk2 = CCSprite::create("myPic/img_bg_5.jpg");
	m_bk2->setAnchorPoint(Vec2(0, 0));
	m_bk2->setPosition(0, m_bk2->getContentSize().height);
	this->addChild(m_bk2);
	this->schedule(schedule_selector(GameScene::backgroundmove), 0.01);
}

void BaiYangGameScene::setLayer()
{
	EnemyLayer::m_BossSprite = NULL;
	m_enemy = FirstSceneEnemyLayer::create();
	m_enemy->StartEnemyPlane();
	m_enemy->StartBossMode();
	this->addChild(m_enemy, EnemyLayerZOrder);


	m_bossBulletLayer = BossEnemyBulletLayer::create();
	this->addChild(m_bossBulletLayer,BossBulletLayerZOrder);
}

void BaiYangGameScene::removeBoss(Node * pSender)
{
	this->m_enemy->removeChild((Sprite*)pSender);
	EnemyLayer::m_BossSprite = NULL;
	menuPauseCallBack(NULL);
}

void JuXieGameScene::setBackground()
{
	m_bk1 = CCSprite::create("myPic/img_bg_4.jpg");
	m_bk1->setAnchorPoint(Vec2(0, 0));
	m_bk1->setPosition(0, 0);
	this->addChild(m_bk1);
	m_bk2 = CCSprite::create("myPic/img_bg_4.jpg");
	m_bk2->setAnchorPoint(Vec2(0, 0));
	m_bk2->setPosition(0, m_bk2->getContentSize().height);
	this->addChild(m_bk2);
	this->schedule(schedule_selector(GameScene::backgroundmove), 0.01);
}

void JuXieGameScene::setLayer()
{
	EnemyLayer::m_BossSprite = NULL;
	m_enemy = SecondSceneEnemyLayer::create();
	m_enemy->StartEnemyPlane();
	m_enemy->StartBossMode();
	this->addChild(m_enemy, EnemyLayerZOrder);


	m_bossBulletLayer = FirsBossBulletLayer::create();
	this->addChild(m_bossBulletLayer,BossBulletLayerZOrder);
}

void JuXieGameScene::removeBoss(Node * pSender)
{
	this->m_enemy->removeChild((Sprite*)pSender);
	EnemyLayer::m_BossSprite = NULL;
	menuPauseCallBack(NULL);
}
