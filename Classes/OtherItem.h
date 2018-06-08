#ifndef _OTHER_ITEM_
#define _OTHER_ITEM_

#include<MyActionInterval.h>
#include<GameScene.h>
#include<HelpTool.h>
//#include<BulletLayer.h>
#include<PlayerLayer.h>
#include<EnemyLayer.h>
#pragma once

//道具层
class UFOLayer :public Layer
{
public:
	UFOLayer() {}
	~UFOLayer() {}
	virtual bool init()
	{
		if (Layer::init() == false)
			return false;
		m_daoju = NULL;
		m_zhadan = NULL;

		return true;
	}
	void AddLifeSprite(Node *node);

	void StartUFOMode() {
		this->schedule(schedule_selector(UFOLayer::CreateUfoFunction), 15);
	}
	void CreateUfoFunction(float dt);


	////////////////////////////////////////////////////////////

	CREATE_FUNC(UFOLayer);

	////////////////////////////////////////////////////////////

	//删除道具
	void RemoveUfo(Node *psender) {
		this->removeChild(dynamic_cast<Sprite*>(psender));
		m_daoju = NULL;
	}
	void PengzhuangRemoveDaoju() {
		if (m_daoju) {
			this->removeChild(m_daoju);
			m_daoju = NULL;
		}
	}
	bool isdaojuexit() { return m_daoju != NULL; }

	//捡到炸弹以后左下角加入炸弹图标
	void AddZhaDanSprite(Node *node);

	//bool containTouchPoint(cocos2d::CCTouch* touch);
	//virtual bool onTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	//virtual void onTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	//virtual void onTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);

	struct lifenode {
		Sprite *sprite;
		//int     total_lifenumber;
	};

	Sprite *m_daoju;
	Sprite *m_zhadan;
	//Sprite *m_lifenumber;
	//vector<Sprite> m_lifearry;
	vector<lifenode> m_lifearry;
	int total_lifenumber = 1;

	static int m_ufotype;//0: null;1:炸弹;2:双子弹;3:生命

	static bool m_iszhadan;
	static bool m_isshuangzidan;
	static bool m_islifenumber;
};



class BossEnemyBulletLayer :public Layer
{
public:
	/*friend class GameScene;
	friend class EnemyLayer;*/
	BossEnemyBulletLayer() { m_firstbullet = false; m_secondbullet = false; }
	~BossEnemyBulletLayer() {}
	virtual bool init();
	virtual void AddBossFirstBullet(float dt);
	virtual void AddBossSecondBullet(float dt);
	virtual void AddBossThirdBullet(float dt);
	virtual void AddBossFourthBullet(float dt);
	virtual void Addmissile(float dt);
	void MissileMove(Node*pSender);
	virtual void BulletMove(Node *pSender, int, float radius, Point);
	void RemoveBossEnemyBullet(Node* pSender);
	void RemoveBossMissile(Node *pSender);
	//void RemoveBossMissile(Node* pSender);
	virtual void StartBossShoot() { //开始发射子弹
							//this->schedule(schedule_selector(BossEnemyBulletLayer::AddBossFirstBullet), 0.8f); 
		this->schedule(schedule_selector(BossEnemyBulletLayer::AddBossSecondBullet), 5.0f);
		this->schedule(schedule_selector(BossEnemyBulletLayer::AddBossThirdBullet), 2.5f);
		this->schedule(schedule_selector(BossEnemyBulletLayer::AddBossFourthBullet), 7.5f);
		this->schedule(schedule_selector(BossEnemyBulletLayer::Addmissile), 2.0f);
	};
	//未使用
	virtual void StopBossShoot() {
		this->unschedule(schedule_selector(BossEnemyBulletLayer::AddBossFirstBullet));
	};
	//void SetOneRedBullet() { m_firstbullet = true; m_secondbullet = false; }
	//void SetTwoBlueBullet() { m_secondbullet = true; m_firstbullet = false; }
	CREATE_FUNC(BossEnemyBulletLayer);

	struct  node
	{
		Sprite* sprite;
		int life;
	};

	static const int m_speed = 350;
	bool m_firstbullet;
	bool m_secondbullet;
	Vec2 m_startpos;
	vector<Sprite*> m_bossbullet;
	vector<node> m_bossmissilearry;
};

class FirsBossBulletLayer:public BossEnemyBulletLayer
{
public:
	FirsBossBulletLayer(){};
	~FirsBossBulletLayer(){};
	CREATE_FUNC(FirsBossBulletLayer);

	void AddBossThirdBullet(float dt);

	void StartBossShoot() { //开始发射子弹
									//this->schedule(schedule_selector(BossEnemyBulletLayer::AddBossFirstBullet), 0.8f); 
		//this->scheduleOnce(schedule_selector(BossEnemyBulletLayer::AddBossSecondBullet), 5.0f);
		this->schedule(schedule_selector(BossEnemyBulletLayer::AddBossThirdBullet), 0.1f,10,5.0f);
		//this->scheduleOnce(schedule_selector(BossEnemyBulletLayer::AddBossFourthBullet), 7.5f);
		this->scheduleOnce(schedule_selector(BossEnemyBulletLayer::Addmissile), 4.0f);
		this->schedule(schedule_selector(FirsBossBulletLayer::addJuXieBulletOne), 0.1f,20,11.0f);
		this->schedule(schedule_selector(FirsBossBulletLayer::addJuXieRandomBullet),0.1f,20,16.0f);
		this->schedule(schedule_selector(FirsBossBulletLayer::addJuXieCrossBullet), 0.1f, 15, 19.0f);
		this->schedule(schedule_selector(FirsBossBulletLayer::addJuXieCircleBullet),0.1f,20,23.0f);
	};

private:
	void addJuXieBulletOne(float dt);
	void addJuXieStars(float dt);
	int STARS_NUM=0;

	void addJuXieRandomBullet(float dt);
	
	void addJuXieCrossBullet(float dt);

	void addJuXieCircleBullet(float dt);

};


#endif