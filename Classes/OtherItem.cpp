#include<OtherItem.h>

int UFOLayer::m_ufotype = 0;
bool UFOLayer::m_iszhadan = false;
bool UFOLayer::m_isshuangzidan = false;
bool UFOLayer::m_islifenumber = false;

//加入道具
void UFOLayer::CreateUfoFunction(float dt) {
	int n = rand() % 3;
	if (n == 0) {
		m_daoju = Sprite::create("ThunderNew/vipicon001.png");//子弹

		m_ufotype = ShuangZidan;//shuangzidan
		m_isshuangzidan = true;
		//m_iszhadan=false;//设置炸弹为空
	}
	else if (n == 1) {
		m_daoju = Sprite::create("ThunderNew/vipicon015.png");//炸弹
		m_ufotype = ZhaDan;//zhadan
		m_iszhadan = true;
		//m_isshuangzidan=false;//设置子弹为单子弹
	}
	else {
		m_daoju = Sprite::create("ThunderNew/vipicon018.png");//命
		m_ufotype = Life;
		m_islifenumber = true;
	}
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 newpos;
	newpos.x = origin.x + rand() % (int)size.width;
	newpos.y = origin.y + size.height;
	m_daoju->setPosition(newpos);
	this->addChild(m_daoju, PlaneLayerZOrder);
	CCFiniteTimeAction *action = CCMoveTo::create(3, newpos - Vec2(0, size.height));
	CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(UFOLayer::RemoveUfo));
	m_daoju->runAction(Sequence::create(action, actiondone, NULL));
}


void UFOLayer::AddZhaDanSprite(Node* node)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_zhadan = Sprite::create("myPic/zhadan-01.png");
	m_zhadan->setAnchorPoint(Vec2(0, 0));
	m_zhadan->setPosition(origin.x + 20, origin.y + 20);
	node->addChild(m_zhadan, PlaneLayerZOrder, ZhaDanTag);
}


//捡到飞机以后在右下角加入飞机图标
void UFOLayer::AddLifeSprite(Node *node)
{
	if (total_lifenumber<3 && total_lifenumber>0) {
		Sprite *m_life;
		CCSize visibleSize = Director::getInstance()->getVisibleSize();

		Vec2 origion = Director::getInstance()->getVisibleOrigin();
		m_life = Sprite::create("ThunderNew/vipbox.png");
		m_life->setAnchorPoint(Vec2(0, 0));


		m_life->setPosition(origion.x + visibleSize.width - 150 - (total_lifenumber - 1) * 60, origion.y + 50);
		node->addChild(m_life, PlaneLayerZOrder);
		lifenode lifen;
		lifen.sprite = m_life;

		m_lifearry.push_back(lifen);//将小飞机图标添加到一个数组下，便于操作（删除）
		total_lifenumber++;
	}

};

bool BossEnemyBulletLayer::init()
{
	bool bRet = false;
	do
	{
		if (Layer::init() == false)
			return false;
		//m_firstbullet = true;
		//m_secondbullet = false;
		bRet = true;
	} while (0);
	return bRet;
}

//boss开始发射子弹(普通)
void BossEnemyBulletLayer::AddBossFirstBullet(float dt)
{
	auto bossSprtie = EnemyLayer::ShareBoss();
	if (bossSprtie == NULL)
	{
		return;
	}
	//auto spriteframecache = HelpTool::GetFrameCache("bossbullet.plist","bossbullet.png");
	auto bulletsprite = Sprite::create("bullet.png");
	//auto bulletsprite = Sprite::createWithSpriteFrameName("W2.png");
	m_bossbullet.push_back(bulletsprite);
	this->addChild(bulletsprite);
	bulletsprite->setScale(1.5f);
	bulletsprite->setRotation(180.0f);

	auto player = PlayerLayer::SharePlane()->getChildByTag(PlaneNum);
	Size bosssize = bossSprtie->getContentSize();
	Point bosspoint = bossSprtie->getPosition();
	Point playerpoint = player->getPosition();
	bulletsprite->setPosition(bosspoint.x, bosspoint.y - 100);
	int length = sqrt(pow(playerpoint.x - bosspoint.x, 2) + pow(playerpoint.y - bosspoint.y, 2));
	float time = 0.5f;
	if (length<400)
	{
		time = 0.5;
	}
	else
	{
		time = length / 400;
	}
	CCMoveTo* moveto = CCMoveTo::create(time, ccp(playerpoint.x, playerpoint.y));
	Point arc;
	arc.x = (playerpoint.x - bosspoint.x) * 3;
	arc.y = (playerpoint.y - (bosspoint.y - 100)) * 3;
	CCMoveBy* movetoedge = CCMoveBy::create(3 * time, ccp(arc.x, arc.y));
	CCSequence *moveseq = CCSequence::create(moveto, movetoedge, NULL);
	CCSequence *seq = CCSequence::create(moveseq, CCCallFuncN::create(this,
		callfuncN_selector(BossEnemyBulletLayer::RemoveBossEnemyBullet)), NULL);

	bulletsprite->runAction(seq);
}
//为boss添加第二种子弹
void BossEnemyBulletLayer::AddBossSecondBullet(float dt)
{
	auto bossSprtie = EnemyLayer::ShareBoss();
	if (bossSprtie == NULL)
	{
		return;
	}
	auto player = PlayerLayer::SharePlane()->getChildByTag(PlaneNum);
	Size bosssize = bossSprtie->getContentSize();
	Point bosspoint = bossSprtie->getPosition();
	Point playerpoint = player->getPosition();
	for (int i = 0; i < 10; i++)
	{
		float xPos = bosspoint.x - 150 + i * 30;
		float xEndPos = xPos - 400 + (i % 5) * 100;
		float yPos = bosspoint.y - bosssize.height / 3 + (i % 5 * 10);
		if (i>4)
		{
			xEndPos = xPos + (i % 5) * 100;
			yPos = bosspoint.y - bosssize.height / 3 + 40 - (i % 5 * 10);
		}
		auto bullet = Sprite::create("ThunderNew/bullet-01-1.png");
		m_bossbullet.push_back(bullet);
		this->addChild(bullet);
		bullet->setScale(1.5f);
		bullet->setRotation(180.0f);
		//bullet->setPosition(xPos,yPos);
		bullet->setPosition(bosspoint);

		CCRotateBy *rotaBy1 = CCRotateBy::create(0.5, 90, 45);
		auto act = CCRepeatForever::create(rotaBy1);

		CCMoveTo* moveto1 = CCMoveTo::create(0.5, ccp(xPos, yPos));
		CCMoveTo* moveto2 = CCMoveTo::create(1.4f, ccp(xEndPos, -10));
		CCSequence *moveseq = CCSequence::create(moveto1, moveto2, NULL);
		CCSequence *seq = CCSequence::create(moveseq, CCCallFuncN::create(this,
			callfuncN_selector(BossEnemyBulletLayer::RemoveBossEnemyBullet)), NULL);

		bullet->runAction(seq);
	}
}

//添加Boss第三种子弹
void BossEnemyBulletLayer::AddBossThirdBullet(float dt)
{
	auto bossSprtie = EnemyLayer::ShareBoss();
	if (bossSprtie == NULL)
	{
		return;
	}
	auto player = PlayerLayer::SharePlane()->getChildByTag(PlaneNum);
	Size bosssize = bossSprtie->getContentSize();
	Point bosspoint = bossSprtie->getPosition();
	Point playerpoint = player->getPosition();

	float radianOnce = 2 * M_PI / 12;//每次位置变换弧度
	float radian = 0.0f;
	float radius = 60;//半径
	int speed = 400;
	float time = 0.5;
	for (int tmpi = 0; tmpi < 24; tmpi++)
	{
		if (tmpi>11)
		{
			radius = 30;
		}
		int i = tmpi % 12;
		radian = radianOnce*(i + 1);
		float xPos = radius*sin(radian) + bosspoint.x;
		float yPos = radius*cos(radian) + bosspoint.y;

		auto bullet = Sprite::create("ThunderNew/bullet-02.png");
		m_bossbullet.push_back(bullet);
		this->addChild(bullet);
		bullet->setScale(1.5f);
		//bullet->setRotation(180.0f);
		bullet->setPosition(bosspoint);

		float xArc = (xPos - bosspoint.x) * 70;
		float yArc = (yPos - bosspoint.y) * 70;
		int length = sqrt(pow(xArc, 2) + pow(yArc, 2));
		time = length / speed;

		auto rotateto = RotateBy::create(0.5f, 360);
		auto actrepeat = RepeatForever::create(rotateto);

		bullet->runAction(actrepeat);

		auto move1 = CCMoveTo::create(0.4, ccp(xPos, yPos));
		auto move2 = CCMoveBy::create(time, ccp(xArc, yArc));
		CCSequence *moveseq = CCSequence::create(move1, move2, NULL);
		auto spawn = CCSpawn::create(moveseq, NULL);
		CCSequence *seq = CCSequence::create(spawn, CCCallFuncN::create(this,
			callfuncN_selector(BossEnemyBulletLayer::RemoveBossEnemyBullet)), NULL);

		bullet->runAction(seq);
	}
}

void BossEnemyBulletLayer::AddBossFourthBullet(float dt)
{
	auto bossSprtie = EnemyLayer::ShareBoss();

	if (bossSprtie == NULL)
	{
		return;
	}

	auto player = PlayerLayer::SharePlane()->getChildByTag(PlaneNum);
	Size bosssize = bossSprtie->getContentSize();
	Point bosspoint = bossSprtie->getPosition();
	Point playerpoint = player->getPosition();
	float radianOnce = 2 * M_PI / 30;//每次位置变换弧度
	float radian = 0.0f;
	float radius = 5;//半径
	int speed = 400;
	float time = 0.5;
	//CCSequence *seq = CCSequence::create(NULL, CCCallFuncN::create(this,
	//	callfuncN_selector(BossEnemyBulletLayer::BulletMove)), NULL);

	//float radianOnce = 2 * M_PI / 12;
	//float radian = 0.0f;//总弧度
	//float radius = 50;//半径
	//////////////////////////////////////////////////////////
	for (int i = 0; i < 24; i++)
	{
		radian = radianOnce*(i + 1);
		auto bullet = Sprite::create("ThunderNew/bullet-03.png");
		m_bossbullet.push_back(bullet);
		this->addChild(bullet);
		//bullet->setRotation(180.0f);
		bullet->setPosition(bosspoint);
		float xPos = radius*sin(radian) + bosspoint.x;
		float yPos = radius*cos(radian) + bosspoint.y;

		auto move1 = CCMoveTo::create(0.1f, ccp(bosspoint.x, bosspoint.y - 40));
		auto move2 = CCMoveTo::create(0.5f, ccp(xPos, yPos));
		CCSequence *moveseq = CCSequence::create(move2, NULL);
		auto action = Sequence::create(
			moveseq,
			CallFuncN::create(CC_CALLBACK_1(BossEnemyBulletLayer::BulletMove, this, i, radius, bosspoint)), NULL);

		bullet->runAction(action);
	}


	///////////////////////////////////////////////////////////


}

void BossEnemyBulletLayer::Addmissile(float dt)
{
	auto boss = EnemyLayer::ShareBoss();
	if (!boss)
	{
		return;
	}
	Point p = boss->getPosition();
	//auto sprite = Sprite::create("atomicBomb.png");
	auto sprite = HelpTool::GetSpriteByFileName("ThunderNew/rocket-01.png", 1);
	//sprite->setScale(0.4);
	//sprite->setRotation(180.0f);
	this->addChild(sprite, EnemyLayerZOrder);
	sprite->setPosition(p);
	sprite->setTag(Missile);
	node n;
	n.life = MissileLife;
	n.sprite = sprite;
	m_bossmissilearry.push_back(n);

	MissileMove(sprite);

}

void BossEnemyBulletLayer::MissileMove(Node* pSender)
{
	auto boss = EnemyLayer::ShareBoss();
	if (!boss)
	{
		return;
	}
	//Rect boosrect = HelpTool::GetSpritePosition(boss);
	Point bosspoint = boss->getPosition();
	auto player = (Sprite*)
		(PlayerLayer::SharePlane()->getChildByTag(PlaneNum));
	//Rect playerrect = HelpTool::GetSpritePosition(player);
	Point playerPoint = player->getPosition();
	auto missile = (Sprite*)pSender;
	//Rect missilerect = HelpTool::GetSpritePosition(missile);
	Point missilePoint = missile->getPosition();
	float radius = 50;
	float xarc = playerPoint.x - missilePoint.x;
	float yarc = playerPoint.y - missilePoint.y;
	//float radian =180.0f+ (atan((xarc)/(yarc))/(2*M_PI))*360.0f;
	float radian = (atan((xarc) / (yarc)) / (2 * M_PI))*360.0f;
	float time = 0.2f;
	float movex = radius*sin(abs(atan(xarc / yarc)));
	float movey = radius*cos(abs(atan(xarc / yarc)));

	CCMoveBy* moveby = CCMoveBy::create(time, ccp(movex, movey));
	//CCMoveTo* moveto = CCMoveTo::create(0.5,playerPoint);
	if (playerPoint.y<missilePoint.y)
	{

		movey = (0 - movey);
	}
	else
	{
		radian = (atan((xarc) / (yarc)) / (2 * M_PI))*360.0f;
	}

	if (playerPoint.x<missilePoint.x)//玩家在导弹的左边
	{
		movex = (0 - movex);
	}

	if (playerPoint.y>bosspoint.y)
	{
		radian = (atan((xarc) / (yarc)) / (2 * M_PI))*360.0f;
	}

	CCRotateTo* rotato = CCRotateTo::create(time, radian);
	moveby = CCMoveBy::create(time, ccp(movex, movey));
	CCSpawn* spwan = CCSpawn::create(rotato, moveby, NULL);
	auto action = Sequence::create(
		spwan,
		CallFuncN::create(CC_CALLBACK_1(BossEnemyBulletLayer::MissileMove, this)), NULL);
	missile->runAction(action);
}

void BossEnemyBulletLayer::BulletMove(Node * pSender, int times, float radius, Point point)
{
	times++;
	auto bullet = (Sprite*)(pSender);
	auto bulletPosition = bullet->getPosition();
	float radian = 0.0f;//总弧度
	float radianOnce = 2 * M_PI / 30;//每次位置变换弧度

	radian = radianOnce*(times % 31);
	float roatRadian = (times % 31)*(360 / 30);
	float xPos = radius*sin(radian) + point.x;
	float yPos = radius*cos(radian) + point.y;
	//point.y = bulletPosition.y;
	radius = radius + 15;//半径

	float time = 2 * M_PI*radius*radianOnce / 2500;

	auto move1 = CCMoveTo::create(time, ccp(xPos, yPos));
	auto move2 = CCRotateTo::create(time, roatRadian - 180);
	auto *movespawn = CCSpawn::create(move1, move2, NULL);
	auto action = Sequence::create(
		movespawn,
		CallFuncN::create(CC_CALLBACK_1(BossEnemyBulletLayer::BulletMove, this, times, radius, point)), NULL);
	if (yPos <= 0)
	{
		action = Sequence::create(
			movespawn,
			CallFuncN::create(CC_CALLBACK_1(BossEnemyBulletLayer::RemoveBossEnemyBullet, this)), NULL);
	}

	bullet->runAction(action);
}

void BossEnemyBulletLayer::RemoveBossEnemyBullet(Node * pSender)
{

	Sprite *psender = dynamic_cast<Sprite*>(pSender);
	typedef vector<Sprite*>::iterator Iter;
	for (Iter it = m_bossbullet.begin(); it != m_bossbullet.end(); ++it)
	{
		if (*it == psender) {
			m_bossbullet.erase(it);
			this->removeChild(psender);
			break;
		}
	}
}

void BossEnemyBulletLayer::RemoveBossMissile(Node *pSender)
{
	Sprite *sprite = (Sprite*)pSender;
	typedef vector<node>::iterator Iter;
	for (Iter it =m_bossmissilearry.begin(); it != m_bossmissilearry.end(); ++it)
	{
		if (it->sprite == sprite)
		{
			this->removeChild(it->sprite);
			m_bossmissilearry.erase(it);
			break;
		}
	}
}

void FirsBossBulletLayer::AddBossThirdBullet(float dt)
{
	auto bossSprtie = EnemyLayer::ShareBoss();
	if (bossSprtie == NULL)
	{
		return;
	}
	auto player = PlayerLayer::SharePlane()->getChildByTag(PlaneNum);
	Size bosssize = bossSprtie->getContentSize();
	Point bosspoint = bossSprtie->getPosition();
	Point playerpoint = player->getPosition();

	float radianOnce = 2 * M_PI / 12;//每次位置变换弧度
	float radian = 0.0f;
	float radius = 60;//半径
	int speed = 400;
	float time = 0.5;
	for (int tmpi = 0; tmpi < 24; tmpi++)
	{
		int i = tmpi % 12;
		radian = radianOnce*(i + 1);

		
		Sprite * bullet = Sprite::create("ThunderNew/bullet-02.png");;
		if (tmpi>11)
		{
			radian = radian+radianOnce/2;
			bullet = Sprite::create("ThunderNew/points012.png");
			radius = 30;
		}
		float xPos = radius*sin(radian) + bosspoint.x;
		float yPos = radius*cos(radian) + bosspoint.y;

		m_bossbullet.push_back(bullet);
		this->addChild(bullet);
		bullet->setScale(1.5f);
		//bullet->setRotation(180.0f);
		bullet->setPosition(bosspoint);

		float xArc = (xPos - bosspoint.x) * 70;
		float yArc = (yPos - bosspoint.y) * 70;
		int length = sqrt(pow(xArc, 2) + pow(yArc, 2));
		time = length / speed;

		auto rotateto = RotateBy::create(0.5f, 360);
		auto actrepeat = RepeatForever::create(rotateto);

		bullet->runAction(actrepeat);

		auto move1 = CCMoveTo::create(0.4, ccp(xPos, yPos));
		auto move2 = CCMoveBy::create(time, ccp(xArc, yArc));
		CCSequence *moveseq = CCSequence::create(move1, move2, NULL);
		auto spawn = CCSpawn::create(moveseq, NULL);
		CCSequence *seq = CCSequence::create(spawn, CCCallFuncN::create(this,
			callfuncN_selector(BossEnemyBulletLayer::RemoveBossEnemyBullet)), NULL);

		bullet->runAction(seq);
	}
}

void FirsBossBulletLayer::addJuXieBulletOne(float dt)
{
	//auto bossSprtie = EnemyLayer::ShareBoss();
	//this->scheduleOnce(schedule_selector(FirsBossBulletLayer::addJuXieStars),0.1f);
	addJuXieStars(0);
}

void FirsBossBulletLayer::addJuXieStars(float dt)
{
	auto bossSprtie = EnemyLayer::ShareBoss();


	if (bossSprtie == NULL)
	{
		return;
	}

	Size bosssize = bossSprtie->getContentSize();
	Point bosspoint = bossSprtie->getPosition();

	float radianOnce = 2 * M_PI / 90;//每次位置变换弧度
	float radian = 0.0f;
	float radius = 60;//半径
	int speed = 400;
	float time = 0.5;
	for (int tempi = 0; tempi < 3; tempi++)
	{
		STARS_NUM++;
		////////////////////////////////////////////////////
		int i = STARS_NUM % 90;
		radian = radianOnce*(i + 1)+(tempi*(2*M_PI/3));
		float xPos = radius*sin(radian) + bosspoint.x;
		float yPos = radius*cos(radian) + bosspoint.y;

		auto bullet = Sprite::create("myPic/bullet_01_02.png");
		node n;
		n.life = SceneJuXieStarsLife;
		n.sprite = bullet;
		m_bossmissilearry.push_back(n);
		this->addChild(bullet,BossBulletLayerZOrder,JuXieStarsTag);
		bullet->setPosition(xPos, yPos);

		float xArc = (xPos - bosspoint.x) * 70;
		float yArc = (yPos - bosspoint.y) * 70;
		int length = sqrt(pow(xArc, 2) + pow(yArc, 2));
		time = length / (0.8*speed);

		auto rotateto = RotateBy::create(0.5f, 360);
		auto actrepeat = RepeatForever::create(rotateto);

		bullet->runAction(actrepeat);

		auto move2 = CCMoveBy::create(time, ccp(xArc, yArc));
		CCSequence *moveseq = CCSequence::create(move2, NULL);
		auto spawn = CCSpawn::create(moveseq, NULL);
		CCSequence *seq = CCSequence::create(spawn, CCCallFuncN::create(this,
			callfuncN_selector(BossEnemyBulletLayer::RemoveBossMissile)), NULL);

		bullet->runAction(seq);

	}

	
}

void FirsBossBulletLayer::addJuXieRandomBullet(float dt)
{
	auto boss = EnemyLayer::ShareBoss();
	auto bosspoint = boss->getPosition();
	auto bosssize = boss->getContentSize();
	auto contentsize = Director::getInstance()->getVisibleSize();

	auto leftSprite =Sprite::create("ThunderNew/bullet-02.png") ;
	auto rightSprite = Sprite::create("ThunderNew/bullet-02.png");

	float xleftpos = bosspoint.x-bosssize.width/4;
	float yleftpos = bosspoint.y-bosssize.height/2;
	float xrightpos = bosspoint.x + bosssize.width / 4;
	float yrightpos = bosspoint.y - bosssize.height / 2;;
	leftSprite->setPosition(xleftpos,yleftpos);
	rightSprite->setPosition(xrightpos,yrightpos);
	m_bossbullet.push_back(leftSprite);
	m_bossbullet.push_back(rightSprite);

	auto leftrote = RotateBy::create(0.5f,360);
	auto rightrote = RotateBy::create(0.5f,360);
	leftSprite->runAction(RepeatForever::create(leftrote));
	rightSprite->runAction(RepeatForever::create(rightrote));

	this->addChild(leftSprite);
	this->addChild(rightSprite);
	float xleftEndPos = rand() % 60 * (contentsize.width / 60);
	float yleftEndPos = -10;
	float xrightEndPos = rand() % 60 * (contentsize.width / 60);
	float yrightEndPos = -10;
	auto leftRandomMove = MoveTo::create(1.5f,ccp(xleftEndPos,yleftEndPos));
	auto rightRandomMove = MoveTo::create(1.5f, ccp(xrightEndPos, yrightEndPos));

	auto *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(BossEnemyBulletLayer::RemoveBossEnemyBullet));

	leftSprite->runAction(Sequence::create(leftRandomMove,actiondone,NULL));
	rightSprite->runAction(Sequence::create(rightRandomMove, actiondone, NULL));
}

void FirsBossBulletLayer::addJuXieCrossBullet(float dt)
{
	auto boss = EnemyLayer::ShareBoss();
	auto bosspoint = boss->getPosition();
	auto bosssize = boss->getContentSize();
	auto contentsize = Director::getInstance()->getVisibleSize();

	auto leftSprite = Sprite::create("ThunderNew/bullet-01-d.png");
	auto rightSprite = Sprite::create("ThunderNew/bullet-01-d.png");

	float xleftpos = bosspoint.x - 2*bosssize.width / 5;
	float yleftpos = bosspoint.y - bosssize.height / 3;
	float xrightpos = bosspoint.x + 2*bosssize.width / 5;
	float yrightpos = bosspoint.y - bosssize.height / 3;
	leftSprite->setPosition(xleftpos, yleftpos);
	rightSprite->setPosition(xrightpos, yrightpos);
	m_bossbullet.push_back(leftSprite);
	m_bossbullet.push_back(rightSprite);

	auto leftrote = RotateBy::create(0.5f, 360);
	auto rightrote = RotateBy::create(0.5f, 360);
	leftSprite->runAction(RepeatForever::create(leftrote));
	rightSprite->runAction(RepeatForever::create(rightrote));

	this->addChild(leftSprite);
	this->addChild(rightSprite);
	float xleftEndPos = (contentsize.width / 2)+200;
	float yleftEndPos = -10;
	float xrightEndPos = (contentsize.width / 2)-200;
	float yrightEndPos = -10;
	auto leftMove = MoveTo::create(1.5f, ccp(xleftEndPos, yleftEndPos));
	auto rightMove = MoveTo::create(1.5f, ccp(xrightEndPos, yrightEndPos));

	auto *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(BossEnemyBulletLayer::RemoveBossEnemyBullet));

	leftSprite->runAction(Sequence::create(leftMove, actiondone, NULL));
	rightSprite->runAction(Sequence::create(rightMove, actiondone, NULL));
}

void FirsBossBulletLayer::addJuXieCircleBullet(float dt)
{
	auto boss = EnemyLayer::ShareBoss();
	auto bosspoint = boss->getPosition();
	auto bosssize = boss->getContentSize();
	auto contentsize = Director::getInstance()->getVisibleSize();
	
	float radanOnce = 2 * M_PI / 8;

	auto leftsprite = Sprite::create("ThunderNew/bullet-01-d.png");
	leftsprite->setPosition(ccp(bosspoint.x,bosspoint.y));
	this->addChild(leftsprite);
	m_bossbullet.push_back(leftsprite);
	auto rightsprite = Sprite::create("ThunderNew/bullet-01-c.png");
	rightsprite->setPosition(ccp(bosspoint.x, bosspoint.y));
	this->addChild(rightsprite);
	m_bossbullet.push_back(rightsprite);

	MyEllipsesConfig myleftellipsesconfig;
	myleftellipsesconfig.aLength = 150;
	myleftellipsesconfig.centerPosition = ccp(bosspoint.x+5,bosspoint.y);
	myleftellipsesconfig.cLength = 130;
	//default left

	MyEllipsesConfig myrightellipsesconfig;
	myrightellipsesconfig.aLength = 150;
	myrightellipsesconfig.centerPosition =ccp(bosspoint.x+bosssize.width,bosspoint.y);
	myrightellipsesconfig.cLength = 130;
	myrightellipsesconfig.LeftOrRight = 1;//right

	auto action1 = MySpecialEllipsesBy::Create(3.0f,myleftellipsesconfig);
	auto action2 = MySpecialEllipsesBy::Create(3.0f, myrightellipsesconfig);
	auto *actiondone = CCCallFuncN::create(this,
		callfuncN_selector(BossEnemyBulletLayer::RemoveBossEnemyBullet));

	leftsprite->runAction(Sequence::create(Repeat::create(action1, 2),actiondone,NULL));
	rightsprite->runAction(Sequence::create(Repeat::create(action2, 2), actiondone, NULL));
}
