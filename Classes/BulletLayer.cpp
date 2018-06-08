#include <BulletLayer.h>

bool BulletLayer::init()
{
	bool bRet = false;
	do
	{
		if (Layer::init() == false)
			return false;
		m_firstbullet = true;
		m_secondbullet = false;
		//m_secondbullet = true;
		m_bulletNum = 0;
		/*	m_firstbullet = false;
		m_secondbullet = true;
		m_bulletNum = 2; */
		bRet = true;
	} while (0);
	return bRet;
}
//开始射击 
void BulletLayer::StartShoot()
{
	this->schedule(schedule_selector(BulletLayer::AddBullet), 0.2);
}

//发射子弹
void BulletLayer::AddBullet(float dt)
{
	auto spriteframecache = HelpTool::GetFrameCache("Longbullet.plist", "Longbullet.png");
	SpriteFrame *frame[2];
	SpriteFrame *frame1[2];
	string tmpstr = "";
	string str = "";
	auto animation = CCAnimation::create();
	auto animation1 = CCAnimation::create();
	for (int i = 0; i < 2; i++)
	{
		CCString *num = CCString::createWithFormat("%d", i + 1);
		string numstr = num->_string.c_str();
		tmpstr = "" + numstr;
		str = "bullet_" + tmpstr + ".png";

		frame[i] = spriteframecache->getSpriteFrameByName(str);
		frame1[i] = spriteframecache->getSpriteFrameByName(str);
		animation->addSpriteFrame(frame[i]);
		animation1->addSpriteFrame(frame1[i]);
	}
	animation->setDelayPerUnit(0.3f);
	animation1->setDelayPerUnit(0.3f);
	auto animate = CCAnimate::create(animation);
	auto animate1 = CCAnimate::create(animation1);

	Sprite* sprite = NULL;
	Sprite* sprite1 = NULL;
	Sprite* spriteleft = NULL;
	Sprite* spriteright = NULL;
	/*Sprite *sprite=NULL;
	Sprite *sprite1=NULL;*/
	//if(UFOLayer::m_isshuangzidan==true){
	//	m_secondbullet=true;
	//	m_firstbullet=false;
	//}
	//else if(UFOLayer::m_isshuangzidan==false){
	//	m_firstbullet=true;
	//	m_secondbullet=false;
	//}
	if (m_secondbullet)
	{
		m_firstbullet = false;
	}
	else
	{
		m_secondbullet = false;
		m_firstbullet = true;
	}

	Vec2 vec = PlayerLayer::SharePlane()->getChildByTag(PlaneNum)->getPosition();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size = PlayerLayer::SharePlane()->getChildByTag(PlaneNum)->getContentSize();
	Size visiblesize = Director::getInstance()->getVisibleSize();
	//单个子弹
	if (m_firstbullet) {
		sprite = Sprite::create("ThunderNew/shouweizidan.png");
		m_bullet.push_back(sprite);

		m_startpos = vec + Size(0, 50);
		//m_startpos=vec+Size(0,size.height/2);
		//m_startpos = Size(100, size.height / 2);
		sprite->setPosition(m_startpos);
		this->addChild(sprite);

		//sprite->runAction(CCRepeatForever::create(animate));

		int length = visiblesize.height + origin.y - m_startpos.y;
		int time = length / m_speed;
		CCFiniteTimeAction *action = CCMoveTo::create(time, Vec2(m_startpos.x, visiblesize.height + origin.y + 100));
		CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
			callfuncN_selector(BulletLayer::RemoveBullet));
		sprite->runAction(CCSequence::create(action, actiondone, NULL));
	}
	//N个子弹
	else if (m_secondbullet) {
		//sprite=Sprite::create("bullet0.png");
		//sprite1=Sprite::create("bullet0.png");
		CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
			callfuncN_selector(BulletLayer::RemoveBullet));
		if (m_bulletNum>1)
		{
			spriteleft = Sprite::createWithSpriteFrame(frame[0]);
			spriteleft->setScale(0.6);
			spriteright = Sprite::createWithSpriteFrame(frame[0]);
			spriteright->setScale(0.6);
			m_bullet.push_back(spriteleft);
			m_bullet.push_back(spriteright);
			this->addChild(spriteleft);
			this->addChild(spriteright);
			Vec2 startleft = m_startpos + Vec2(-20 - 30, -10);
			Vec2 startright = m_startpos + Vec2(20 + 30, -10);
			spriteleft->setPosition(startleft);
			spriteright->setPosition(startright);
			Point endposleft = startleft - Vec2(visiblesize.width / 2, -(visiblesize.height));
			Point endposright = startleft + Vec2(visiblesize.width / 2, (visiblesize.height));

			////////////// 角度
			float rotation = 90.0f - atan((visiblesize.height) / (visiblesize.width / 2)) / (2 * M_PI)*360.0f;
			spriteleft->setRotation(360.0f - rotation);
			spriteright->setRotation(rotation);
			/////////////////////////
			int lengthleft = sqrt(pow(endposleft.x - startleft.x, 2) + pow(endposleft.y - startleft.y, 2));
			float timeleft = lengthleft / m_speed;
			int lengthright = sqrt(pow(endposright.x - startright.x, 2) + pow(endposright.y - startright.y, 2));
			float timeright = lengthright / m_speed;
			CCFiniteTimeAction *actionleft = CCMoveTo::create(timeleft, endposleft);
			CCFiniteTimeAction *actionright = CCMoveTo::create(timeright, endposright);



			spriteleft->runAction(Sequence::create(actionleft, actiondone, NULL));
			spriteright->runAction(Sequence::create(actionright, actiondone, NULL));
		}
		sprite = Sprite::createWithSpriteFrame(frame[0]);
		sprite1 = Sprite::createWithSpriteFrame(frame[0]);
		sprite->setScale(0.5);
		sprite1->setScale(0.5);

		m_bullet.push_back(sprite);
		m_bullet.push_back(sprite1);

		this->addChild(sprite);
		this->addChild(sprite1);
		CCAction * animateAction = CCRepeatForever::create(animate);
		CCAction * animateAction1 = CCRepeatForever::create(animate1);
		m_startpos = vec + Vec2(0, 50);
		Vec2 start1 = m_startpos + Vec2(-20, 0);
		Vec2 start2 = m_startpos + Vec2(20, 0);

		sprite->setPosition(start1);
		sprite1->setPosition(start2);

		sprite->runAction(animateAction);
		sprite1->runAction(animateAction1);

		int length = origin.y + visiblesize.height - m_startpos.y;
		int bullettime = length / m_speed;

		CCFiniteTimeAction *action = CCMoveTo::create(bullettime, start1 + Vec2(0, visiblesize.height + 100));
		CCFiniteTimeAction *action1 = CCMoveTo::create(bullettime, start2 + Vec2(0, visiblesize.height + 100));
		CCSpawn *spwan = CCSpawn::create(action, NULL);
		CCSpawn *spwan1 = CCSpawn::create(action1, NULL);
		//CCFiniteTimeAction *actiondone=CCCallFuncN::create(this,
		//	callfuncN_selector(BulletLayer::RemoveBullet));

		sprite->runAction(Sequence::create(spwan, actiondone, NULL));
		sprite1->runAction(Sequence::create(spwan1, actiondone, NULL));
	}
	//SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3",false);
}


void BulletLayer::RemoveBullet(Node* pSender)//传入子弹节点。如果正确，删除传入子弹
{
	Sprite *psender = dynamic_cast<Sprite*>(pSender);
	typedef vector<Sprite*>::iterator Iter;
	for (Iter it = m_bullet.begin(); it != m_bullet.end(); ++it)
	{
		if (*it == psender) {
			m_bullet.erase(it);
			break;
		}
	}
}

void FirstBulletLayer::AddBullet(float dt)
{
	Sprite* sprite = NULL;
	Sprite* sprite1 = NULL;
	Sprite* sprite2 = NULL;
	Sprite* sprite3 = NULL;
	Sprite* spriteleft = NULL;
	Sprite* spriteright = NULL;

	if (m_secondbullet)
	{
		m_firstbullet = false;
	}
	else
	{
		m_secondbullet = false;
		m_firstbullet = true;
	}

	Vec2 vec = PlayerLayer::SharePlane()->getChildByTag(PlaneNum)->getPosition();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size = PlayerLayer::SharePlane()->getChildByTag(PlaneNum)->getContentSize();
	Size visiblesize = Director::getInstance()->getVisibleSize();
	//单个子弹
	if (m_firstbullet) {
		sprite = Sprite::create("myPic/bullet0.png");
		sprite1 = Sprite::create("myPic/bullet0.png");
		m_bullet.push_back(sprite);
		m_bullet.push_back(sprite1);

		m_startpos = vec + Size(-20, 50);
		//m_startpos=vec+Size(0,size.height/2);
		//m_startpos = Size(100, size.height / 2);
		sprite->setPosition(m_startpos);
		sprite1->setPosition(m_startpos.x+40,m_startpos.y);
		this->addChild(sprite);
		this->addChild(sprite1);

		//sprite->runAction(CCRepeatForever::create(animate));

		int length = visiblesize.height + origin.y - m_startpos.y;
		int time = length / m_speed;
		CCFiniteTimeAction *action = CCMoveTo::create(time, Vec2(m_startpos.x, visiblesize.height + origin.y + 100));
		CCFiniteTimeAction *action1 = CCMoveTo::create(time, Vec2(m_startpos.x + 40, visiblesize.height + origin.y + 100));
		CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
			callfuncN_selector(BulletLayer::RemoveBullet));
		sprite->runAction(CCSequence::create(action, actiondone, NULL));
		sprite1->runAction(Sequence::create(action1,actiondone,NULL));
	}
	//N个子弹
	else if (m_secondbullet) {
		CCFiniteTimeAction *actiondone = CCCallFuncN::create(this,
			callfuncN_selector(BulletLayer::RemoveBullet));
		if (m_bulletNum>1)
		{
			spriteleft = Sprite::create("myPic/bullet-s-01.png");
			spriteright = Sprite::create("myPic/bullet-s-01.png");
			m_bullet.push_back(spriteleft);
			m_bullet.push_back(spriteright);
			this->addChild(spriteleft);
			this->addChild(spriteright);
			Vec2 startleft = m_startpos + Vec2(-20 - 30, -10);
			Vec2 startright = m_startpos + Vec2(20 + 30, -10);
			spriteleft->setPosition(startleft);
			spriteright->setPosition(startright);
			Point endposleft = startleft - Vec2(visiblesize.width / 2, -(visiblesize.height));
			Point endposright = startleft + Vec2(visiblesize.width / 2, (visiblesize.height));

			////////////// 角度
			float rotation = 90.0f - atan((visiblesize.height) / (visiblesize.width / 2)) / (2 * M_PI)*360.0f;
			spriteleft->setRotation(360.0f - rotation);
			spriteright->setRotation(rotation);
			/////////////////////////
			int lengthleft = sqrt(pow(endposleft.x - startleft.x, 2) + pow(endposleft.y - startleft.y, 2));
			float timeleft = lengthleft / m_speed;
			int lengthright = sqrt(pow(endposright.x - startright.x, 2) + pow(endposright.y - startright.y, 2));
			float timeright = lengthright / m_speed;
			CCFiniteTimeAction *actionleft = CCMoveTo::create(timeleft, endposleft);
			CCFiniteTimeAction *actionright = CCMoveTo::create(timeright, endposright);



			spriteleft->runAction(Sequence::create(actionleft, actiondone, NULL));
			spriteright->runAction(Sequence::create(actionright, actiondone, NULL));
		}
		sprite = Sprite::create("myPic/bullet-s-01.png");
		sprite1 = Sprite::create("myPic/bullet0.png");
		sprite2 = Sprite::create("myPic/bullet0.png");
		sprite3 = Sprite::create("myPic/bullet-s-01.png");

		m_bullet.push_back(sprite);
		m_bullet.push_back(sprite1);
		m_bullet.push_back(sprite2);
		m_bullet.push_back(sprite3);

		this->addChild(sprite);
		this->addChild(sprite1);
		this->addChild(sprite2);
		this->addChild(sprite3);

		m_startpos = vec + Vec2(0, 50);
		Vec2 start1 = m_startpos + Vec2(-30, 0);
		Vec2 start2 = m_startpos + Vec2(-10, 0);
		Vec2 start3 = m_startpos + Vec2(10, 0);
		Vec2 start4 = m_startpos + Vec2(30, 0);

		sprite->setPosition(start1);
		sprite1->setPosition(start2);
		sprite2->setPosition(start3);
		sprite3->setPosition(start4);



		int length = origin.y + visiblesize.height - m_startpos.y;
		int bullettime = length / m_speed;

		CCFiniteTimeAction *action = CCMoveTo::create(bullettime, start1 + Vec2(0, visiblesize.height + 100));
		CCFiniteTimeAction *action1 = CCMoveTo::create(bullettime, start2 + Vec2(0, visiblesize.height + 100));
		CCFiniteTimeAction *action2 = CCMoveTo::create(bullettime, start3 + Vec2(0, visiblesize.height + 100));
		CCFiniteTimeAction *action3 = CCMoveTo::create(bullettime, start4 + Vec2(0, visiblesize.height + 100));

		sprite->runAction(Sequence::create(action, actiondone, NULL));
		sprite1->runAction(Sequence::create(action1, actiondone, NULL));
		sprite2->runAction(Sequence::create(action2, actiondone, NULL));
		sprite3->runAction(Sequence::create(action3, actiondone, NULL));
	}
}
