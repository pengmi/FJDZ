#include <EnemyLayer.h>

Sprite * EnemyLayer::m_BossSprite = NULL;
int  EnemyLayer::m_BossTotalLife = BossLife;

bool EnemyLayer::init()
{
	bool bRet = false;
	do
	{
		if (Layer::init() == false)
			return false;
		bRet = true;
	} while (0);
	return bRet;
}
//设置boss透明度渐变，也用也player上
void EnemyLayer::SetBossSpriteOpacity(float dt)
{
	if (m_BossSprite == NULL)
	{
		return;
	}

	int add = 20;
	GLubyte gb = m_BossSprite->getOpacity();
	int gbint = gb;
	if (gbint<255)
		m_BossSprite->setOpacity(gbint + add);
	else
	{
		m_BossSprite->setOpacity(255);
		return;
	}
}

//boss的位置控制 在一定范围内不停的移动

void EnemyLayer::BossPositionControl()
{
	if (m_BossSprite == NULL)
		return;
	GLubyte gb = m_BossSprite->getOpacity();
	int gbint = gb;
	if (gb != 255)
	{
		this->schedule(schedule_selector(EnemyLayer::SetBossSpriteOpacity), 0.3);
	}

	Size visiblesize = Director::getInstance()->getVisibleSize();
	float positionX = ((rand() % 5) * 100 - 200) + (visiblesize.width / 2);
	float positionY = ((rand() % 3) * 100 - 100) + (visiblesize.height*0.8);
	int speed = rand() % 3 + 3;

	CCMoveTo *bossMoveTo = CCMoveTo::create(speed, ccp(positionX, positionY));
	CCSequence *seq = CCSequence::create(bossMoveTo, CCCallFunc::create(this,
		callfunc_selector(EnemyLayer::BossPositionControl)), NULL);

	m_BossSprite->runAction(seq);

}

//创建警告信息
void EnemyLayer::CreateWarningMessage(Size *visiblesize)
{
	effectplayedid = SimpleAudioEngine::sharedEngine()->playEffect("sound/bosswaring.mp3", 1);

	m_messageLabel = Label::create();
	m_messageLabel->setString("WARNING UFO IS APPROACHING");
	m_messageLabel->setBMFontFilePath("font/bitmapFontTest.fnt");
	m_messageLabel->setHorizontalAlignment(TextHAlignment::CENTER);

	this->addChild(m_messageLabel);

	m_messageLabel->setPosition(visiblesize->width / 2, visiblesize->height / 2);
	m_messageLabel->setScale(0.2);
	this->schedule(schedule_selector(EnemyLayer::ChangeFontPre), 0.03f);

}

//不断变动字，实现特效
void EnemyLayer::ChangeFontPre(float dt)
{
	if (!m_messageLabel)
		return;
	float scalenownumber = m_messageLabel->getScale();
	float scaleaddnumber = 0.01;

	scalenownumber = scalenownumber + scaleaddnumber;
	m_messageLabel->setScale(scalenownumber);

}

//
void EnemyLayer::RemoveWarningMessage()
{
	SimpleAudioEngine::sharedEngine()->stopEffect(effectplayedid);
	this->removeChild(m_messageLabel);
	m_messageLabel = NULL;
}

//创建boss战机
void EnemyLayer::CreateBoss(float dt)
{

	if (m_BossSprite != NULL)
		return;
	Vect origin = Director::getInstance()->getVisibleOrigin();
	Size visiblesize = Director::getInstance()->getVisibleSize();

	//能成功生成boss的情况下，生成警告
	CreateWarningMessage(&visiblesize);
	//生成Boss的战机
	this->scheduleOnce(schedule_selector(EnemyLayer::CreateBossPlane), 3);
	//敌机出现后，删除警告

}
//创建敌机Boss战机
void EnemyLayer::CreateBossPlane(float dt)
{
	RemoveWarningMessage();

	Vect origin = Director::getInstance()->getVisibleOrigin();
	Size visiblesize = Director::getInstance()->getVisibleSize();

	m_BossTotalLife = BossLife;
	m_BossSprite = Sprite::create("ThunderNew/a-01.png");
	int id = Boss;
	//m_BossSprite->setScale(0.6f);
	m_BossSprite->setOpacity(55);
	this->addChild(m_BossSprite, PlaneLayerZOrder, id);

	Vec2 pos(visiblesize.width / 2, origin.y + visiblesize.height);
	m_BossSprite->setPosition(pos);

	BossPositionControl();
}

//创建敌机
void EnemyLayer::CreateEnemyPlane(float dt)
{
	Sprite *sprite = NULL;
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visiblesize = Director::getInstance()->getVisibleSize();
	int num = rand() % 10;
	int speed = 0;
	int id;
	int life = 0;

	if (num >= 0 && num <= 2)
	{
		sprite = Sprite::create("ThunderNew/c-01.png");
		speed = 3;
		id = LittlePlane;
		life = LittlePlaneLife;
	}
	else if (num >= 3 && num <= 5)
	{
		sprite = Sprite::create("ThunderNew/yunshi-04.png");
		auto rotatedby = RotateBy::create(2.0f, 360);
		auto spwan = CCSpawn::create(rotatedby, NULL);
		sprite->runAction(CCRepeatForever::create(spwan));

		speed = 5;
		id = Bomb;
		life = BombLife;
	}
	else if (num >= 6 && num <= 8)
	{
		sprite = Sprite::create("ThunderNew/c-03.png");
		speed = 5;
		id = BigPlane;
		life = BigPlaneLife;
	}
	else if (num == 9)
	{
		sprite = Sprite::create("ThunderNew/c-05.png");
		auto animation = CCAnimation::create();
		animation->setDelayPerUnit(0.1);
		animation->addSpriteFrameWithFileName("ThunderNew/c-05.png");
		animation->addSpriteFrameWithFileName("ThunderNew/c-05.png");
		auto animate = CCAnimate::create(animation);
		sprite->runAction(CCRepeatForever::create(animate));
		speed = 7;
		id = MorePlane;
		life = MorePlaneLife;
	}
	int randx = origin.x + rand() % (int)visiblesize.width;
	Vec2 pos(randx, origin.y + visiblesize.height);

	sprite->setPosition(pos);
	Vec2 endpos = pos + Vec2(0, -visiblesize.height - 200);

	CCFiniteTimeAction *action = CCMoveTo::create(speed, endpos);
	CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(EnemyLayer::RemoveEnemyPlane));
	sprite->runAction(CCSequence::create(action, actiondone, NULL));

	this->addChild(sprite, PlaneLayerZOrder, id);

	node n;
	n.sprite = sprite;
	n.life = life;
	m_enemyarray.push_back(n);//将敌机放在一个队列里
}

void EnemyLayer::CreateSecondEnemyPlane(float dt)
{
	int id = Pig;
	auto visiblesize = Director::getInstance()->getVisibleSize();
	auto spriteframecache = HelpTool::GetFrameCache("pig.plist", "pig.png");
	for (int j = 0; j < 5; j++)
	{
		float xadd = 50;
		float yadd = 20;//add number for once
		float xstartPos = (-50 * 4 + xadd*j);
		float xmidendPos = visiblesize.width / 2 + xadd*j;
		float xendPos = visiblesize.width + xadd*j;
		float ystartPos = 3 * (visiblesize.height / 4) - yadd*j;
		float ymidendPos = visiblesize.height / 2 - yadd*j;
		float yendPos = 3 * (visiblesize.height / 4) - yadd*j;

		Sprite * pig = Sprite::createWithSpriteFrameName("hero_01.png");
		pig->setPosition(xstartPos, ystartPos);
		this->addChild(pig, PlaneLayerZOrder, id);
		node pigNode;
		pigNode.sprite = pig;
		pigNode.life = PigLife;
		m_enemyarray.push_back(pigNode);

		float xArc1 = xmidendPos - xstartPos;
		float yArc1 = ymidendPos - ystartPos;
		int length1 = sqrt(pow(xArc1, 2) + pow(yArc1, 2));
		float time1 = length1 / 200;

		SpriteFrame *frame[7];
		string tmpstr = "";
		string str = "";
		auto animation = CCAnimation::create();
		for (int i = 0; i < 7; i++)
		{
			CCString *num = CCString::createWithFormat("%d", i + 1);
			string numstr = num->_string.c_str();
			tmpstr = "0" + numstr;
			str = "hero_" + tmpstr + ".png";

			frame[i] = spriteframecache->getSpriteFrameByName(str);
			animation->addSpriteFrame(frame[i]);
		}
		animation->setDelayPerUnit(0.1f);

		auto* animate = CCAnimate::create(animation);
		pig->runAction(CCRepeatForever::create(animate));

		auto moveto1 = MoveTo::create(time1, ccp(xmidendPos, ymidendPos));
		auto moveto2 = MoveTo::create(time1, ccp(xendPos, yendPos));
		CCSequence *moveseq = CCSequence::create(moveto1, moveto2, NULL);
		CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
			callfuncN_selector(EnemyLayer::RemoveEnemyPlane));
		pig->runAction(Sequence::create(moveseq, actiondone, NULL));
	}
}

void EnemyLayer::CreateThirdEnemyPlane(float dt)
{
	int id = Killer;
	if (m_BossSprite == NULL)
	{
		return;
	}

	auto boss = m_BossSprite;
	auto player = PlayerLayer::SharePlane()->getChildByTag(PlaneNum);

	Point playerpoint = player->getPosition();
	Point bosspoint = boss->getPosition();
	float xstartPos, ystartPos;
	float xmidendPos, ymidendPos;
	xstartPos = bosspoint.x;
	ystartPos = bosspoint.y;
	xmidendPos = playerpoint.x;
	ymidendPos = (playerpoint.y + (bosspoint.y - playerpoint.y) / 2);
	auto visiblesize = Director::getInstance()->getVisibleSize();
	float time1 = (bosspoint.y - playerpoint.y) / 600;
	float radius = 180;
	float radianonce = 2 * M_PI / 12;
	/*auto spriteframecache = HelpTool::GetFrameCache("pig.plist", "pig.png");*/
	for (int j = 0; j < 5; j++)
	{
		float totalradian = ((j + 4)*radianonce);
		Sprite * killer = Sprite::create("ThunderNew/c-04.png");
		//killer->setPosition(xstartPos-4*50+j*50, ystartPos+100);
		killer->setPosition(xstartPos, ystartPos);
		this->addChild(killer, PlaneLayerZOrder, id);
		node killerNode;
		killerNode.sprite = killer;
		killerNode.life = KillerLife;
		m_enemyarray.push_back(killerNode);
		//float xfirstpos= xstartPos - 4 * 80 + j * 80, yfirstpos= ystartPos-100;
		float xfirstpos = radius*sin(totalradian) + bosspoint.x;
		float yfirstpos = radius*cos(totalradian) + bosspoint.y;
		float xArc, yArc;
		xArc = xfirstpos - bosspoint.x;
		yArc = yfirstpos - bosspoint.y;
		float xArc1 = xmidendPos - xfirstpos;
		float yArc1 = ymidendPos - yfirstpos;

		//int length1 = sqrt(pow(xArc1, 2) + pow(yArc1, 2));
		//float time1 = length1 / 300;


		auto moveto = MoveTo::create(0.5, ccp(xfirstpos, yfirstpos));
		float radian = (atan((xArc) / (yArc)) / (2 * M_PI))*360.0f;
		auto rotato = RotateTo::create(0.5, radian);
		auto spwan = CCSpawn::create(rotato, moveto, NULL);

		float radian1 = (atan((xArc1) / (yArc1)) / (2 * M_PI))*360.0f;
		auto middlerotato = RotateTo::create(0.7, radian1);

		auto rotato1 = RotateTo::create(time1, radian1);
		auto moveto1 = MoveTo::create(time1, ccp(xmidendPos, ymidendPos));
		auto spwan1 = CCSpawn::create(rotato1, moveto1, NULL);

		CCSequence *moveseq = CCSequence::create(spwan, middlerotato, spwan1, NULL);

		float tana = xArc1 / yArc1;
		if (bosspoint.y>playerpoint.y)
		{
			yArc1 = -200;
		}
		else
		{
			yArc = 200;
		}
		xArc1 = tana * yArc;

		CCFiniteTimeAction *actiondone = CallFuncN::create(
			CC_CALLBACK_1(EnemyLayer::ThirdEnemyMove, this, xArc1, yArc1));
		killer->runAction(Sequence::create(moveseq, actiondone, NULL));
	}
}

void EnemyLayer::CreateFourthEnemyPlane(float dt)
{
	this->unschedule(schedule_selector(EnemyLayer::addStars));
	Sprite * sprite = (Sprite*)this->getChildByTag(StarsPlaneTag);
	if (sprite!=NULL)
	{
		return;
	}
	auto visiblesize = Director::getInstance()->getVisibleSize();
	sprite = Sprite::create("ThunderNew/b-02.png");
	sprite->setPosition(visiblesize.width/2,-50);
	this->addChild(sprite,BossBulletLayerZOrder,StarsPlaneTag);
	
	auto action1 = MoveTo::create(1.5f,ccp(visiblesize.width/2, (visiblesize.height / 3) * 2));
	auto action2 = MoveTo::create(0.5f, ccp(visiblesize.width / 2, (visiblesize.height / 3) * 2));
	auto actiondone = CCCallFuncN::create(this,
		callfuncN_selector(EnemyLayer::CreateStars));
	sprite->runAction(Sequence::create(action1,action2,actiondone,NULL));

}

void EnemyLayer::CreateStars(Node * psender)
{
	auto bossSprtie = (Sprite*)this->getChildByTag(StarsPlaneTag);

	node N;
	N.life = SceneBaiYangKillerLife;
	N.sprite = bossSprtie;
	m_enemyarray.push_back(N);

	this->schedule(schedule_selector(EnemyLayer::addStars),0.1);
	//this->unschedule(schedule_selector(EnemyLayer::addStars));
}

void EnemyLayer::addStars(float dt)
{

	auto bossSprtie =(Sprite*)this->getChildByTag(StarsPlaneTag);


	if (bossSprtie == NULL)
	{
		return;
	}

	Size bosssize = bossSprtie->getContentSize();
	Point bosspoint = bossSprtie->getPosition();

	float radianOnce = 2 * M_PI / 30;//每次位置变换弧度
	float radian = 0.0f;
	float radius = 60;//半径
	int speed = 400;
	float time = 0.5;

	STARS_NUM++;
////////////////////////////////////////////////////
		int i = STARS_NUM % 30;
		radian = radianOnce*(i + 1);
		float xPos = radius*sin(radian) + bosspoint.x;
		float yPos = radius*cos(radian) + bosspoint.y;

		auto bullet = Sprite::create("myPic/points009.png");
		node n;
		n.sprite = bullet;
		n.life = SceneBaiYangKillerMissileLife;
		m_enemyarray.push_back(n);
		this->addChild(bullet);
		bullet->setPosition(xPos,yPos);

		float xArc = (xPos - bosspoint.x) * 70;
		float yArc = (yPos - bosspoint.y) * 70;
		int length = sqrt(pow(xArc, 2) + pow(yArc, 2));
		time = length / (0.8*speed);

		auto rotateto = RotateBy::create(0.5f, 360);
		auto actrepeat = RepeatForever::create(rotateto);

		bullet->runAction(actrepeat);

		//auto move1 = CCMoveTo::create(0.4, ccp(xPos, yPos));
		auto move2 = CCMoveBy::create(time, ccp(xArc, yArc));
		CCSequence *moveseq = CCSequence::create(move2, NULL);
		auto spawn = CCSpawn::create(moveseq, NULL);
		CCSequence *seq = CCSequence::create(spawn, CCCallFuncN::create(this,
			callfuncN_selector(EnemyLayer::RemoveEnemyPlane)), NULL);

		bullet->runAction(seq);
		
}

void EnemyLayer::ThirdEnemyMove(Node *pSender, float xarc, float yarc)
{
	auto sprite = (Sprite*)pSender;
	Point spritepoint = sprite->getPosition();

	float radian = (atan((xarc) / (yarc)) / (2 * M_PI))*360.0f;
	auto moveby1 = MoveBy::create(0.5f, ccp(xarc, yarc));
	auto rotato1 = RotateTo::create(0.5f, radian);
	auto spwan = CCSpawn::create(rotato1, moveby1, NULL);
	CCSequence *moveseq = CCSequence::create(spwan, NULL);

	CCFiniteTimeAction *actiondone = CallFuncN::create(
		CC_CALLBACK_1(EnemyLayer::ThirdEnemyMove, this, xarc, yarc));

	if (spritepoint.y<0)
	{
		actiondone = CCCallFuncN::create(this,
			callfuncN_selector(EnemyLayer::RemoveEnemyPlane));
	}
	sprite->runAction(Sequence::create(moveseq, actiondone, NULL));
}

//传入一个敌机节点，如果正确，销毁敌机
void EnemyLayer::RemoveEnemyPlane(Node *pSender)
{
	Sprite *sprite = (Sprite*)pSender;
	typedef vector<node>::iterator Iter;
	for (Iter it = m_enemyarray.begin(); it != m_enemyarray.end(); ++it)
	{
		if (it->sprite == sprite)
		{
			this->removeChild(it->sprite);
			m_enemyarray.erase(it);
			break;
		}
	}
}

void FirstSceneEnemyLayer::CreateThirdEnemyPlane(float dt)
{
	Sprite* enemyone =(Sprite*)this->getChildByTag(SceneBaiYangKillTagOne);
	Sprite* enemytwo= (Sprite*)this->getChildByTag(SceneBaiYangKillTagTwo);
	if (enemyone!=NULL&&enemytwo!=NULL)
	{
		return;
	}
	enemyone = Sprite::create("ThunderNew/b-03.png");
	enemytwo = Sprite::create("ThunderNew/b-03.png");
	this->addChild(enemyone,BossBulletLayerZOrder,SceneBaiYangKillTagOne);
	this->addChild(enemytwo, BossBulletLayerZOrder, SceneBaiYangKillTagTwo);
	//node n1;
	//node n2;
	//n1.life = SceneBaiYangKillerLife; n1.sprite = enemyone;
	//n2.life = SceneBaiYangKillerLife; n2.sprite = enemytwo;
	//m_enemyarray.push_back(n1);
	//m_enemyarray.push_back(n2);

	auto enemycontentsixe = enemyone->getContentSize();

	auto size = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();

	enemyone->setPosition(origion.x-enemycontentsixe.width/2, (size.height / 8) * 6);
	enemytwo->setPosition(origion.x +size.width+ enemycontentsixe.width / 2,
		(size.height / 8) * 6);

	auto act1 = MoveTo::create(1.0f,ccp(origion.x+(enemycontentsixe.width/2)*2, (size.height / 8) * 6));
	auto act2 = MoveTo::create(1.0f,ccp(origion.x + size.width - 2*(enemycontentsixe.width / 2), 
		(size.height / 8) * 6));
	auto seq1 = Sequence::create(act1, CCCallFuncN::create(this,
		callfuncN_selector(FirstSceneEnemyLayer::CreateMissile)),NULL);
	auto seq2 = Sequence::create(act2, CCCallFuncN::create(this,
		callfuncN_selector(FirstSceneEnemyLayer::CreateMissile)),NULL);
	enemyone->runAction(seq1);
	enemytwo->runAction(seq2);
}

void FirstSceneEnemyLayer::CreateMissile(Node * pSender)
{
	auto sprite = (Sprite*)pSender;
	auto point = sprite->getPosition();

	auto player = PlayerLayer::SharePlane()->getChildByTag(PlaneNum);
	auto playerpoint = player->getPosition();

	//贝塞尔曲线
	for (int i = 0; i < 5; i++)
	{
		auto missile = Sprite::create("myPic/points009.png");
		node n;
		n.life = SceneBaiYangKillerMissileLife;
		n.sprite = missile;
		m_enemyarray.push_back(n);

		missile->setPosition(point.x,point.y-50);

		auto react = RotateBy::create(0.5f, 360);
		this->addChild(missile);
		missile->runAction(RepeatForever::create(react));

		ccBezierConfig tr0;

		tr0.endPosition = ccp(playerpoint.x+(i-2)*100,-10);
		tr0.controlPoint_1 = ccp(i*100+40, 400);
		tr0.controlPoint_2 = ccp(280, 80);
		CCActionInterval* bezierto = CCBezierTo::create(1.5f, tr0);
		auto seq = Sequence::create(bezierto, CCCallFuncN::create(this,
			callfuncN_selector(EnemyLayer::RemoveEnemyPlane)), NULL);
		missile->runAction(seq);
	}

	node n1;
	n1.life = SceneBaiYangKillerLife; n1.sprite = sprite;
	m_enemyarray.push_back(n1);

	auto size = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();
	auto act1 = MoveTo::create(2.0f, ccp(point.x, size.height+100));
	auto act0 = MoveTo::create(1.0f, point);
	auto seq1 = Sequence::create(act0,act1, CCCallFuncN::create(this,
		callfuncN_selector(EnemyLayer::RemoveEnemyPlane)), NULL);
	sprite->runAction(seq1);
}

void FirstSceneEnemyLayer::CreateBoss(float dt)
{
	if (m_BossSprite != NULL)
		return;
	Vect origin = Director::getInstance()->getVisibleOrigin();
	Size visiblesize = Director::getInstance()->getVisibleSize();

	//能成功生成boss的情况下，生成警告
	CreateWarningMessage(&visiblesize);
	//生成Boss的战机
	this->scheduleOnce(schedule_selector(EnemyLayer::CreateBossPlane), 3);
	this->StopCreateEnemyPlane();//停止生产敌机
	//敌机出现后，删除警告
}

void SecondSceneEnemyLayer::CreateBossPlane(float dt)
{
	RemoveWarningMessage();

	Vect origin = Director::getInstance()->getVisibleOrigin();
	Size visiblesize = Director::getInstance()->getVisibleSize();

	m_BossTotalLife = BossLife;
	m_BossSprite = Sprite::create("ThunderNew/a-05.png");
	int id = Boss;
	//m_BossSprite->setScale(0.6f);
	m_BossSprite->setOpacity(55);
	this->addChild(m_BossSprite, PlaneLayerZOrder, id);

	Vec2 pos(visiblesize.width / 2, origin.y + visiblesize.height);
	m_BossSprite->setPosition(pos);

	BossPositionControl();
}
