#ifndef _ENEMY_LAYER_
#define _ENEMY_LAYER_

#include <GameScene.h>
#include<HelpTool.h>
//#include<BulletLayer.h>
#include<PlayerLayer.h>
#include<OtherItem.h>
#pragma once

class EnemyLayer :public Layer
{
public:
	EnemyLayer() {}
	~EnemyLayer() {}
	CREATE_FUNC(EnemyLayer);
	virtual bool init();
	virtual void StartBossMode() { this->schedule(schedule_selector(EnemyLayer::CreateBoss), 5); };
	virtual void StartEnemyPlane() {
		this->schedule(schedule_selector(EnemyLayer::CreateEnemyPlane), 0.7f);
		this->schedule(schedule_selector(EnemyLayer::CreateSecondEnemyPlane), 6.0f);
		this->schedule(schedule_selector(EnemyLayer::CreateThirdEnemyPlane), 10.0f);
	}
	void RemoveEnemyPlane(Node* pSender);//删除敌机
	virtual void CreateBoss(float dt);
	virtual void StopCreateEnemyPlane() {
		this->unschedule(schedule_selector(EnemyLayer::CreateEnemyPlane));
		this->unschedule(schedule_selector(EnemyLayer::CreateSecondEnemyPlane));
		this->unschedule(schedule_selector(EnemyLayer::CreateThirdEnemyPlane));
	};
	virtual void CreateBossPlane(float dt);
	static Sprite * ShareBoss() { return m_BossSprite; };
	void CreateWarningMessage(Size *visiblesize);
	void ChangeFontPre(float dt);
	void RemoveWarningMessage();

	void BossPositionControl();
	void SetBossSpriteOpacity(float dt);
	virtual void CreateEnemyPlane(float dt);//创建敌机
	virtual void CreateSecondEnemyPlane(float dt);//创建敌机
	virtual void CreateThirdEnemyPlane(float dt);//创建敌机
	virtual void CreateFourthEnemyPlane(float dt);
	virtual void CreateMissile(Node* psender){};
	virtual void CreateStars(Node* psender);
	virtual void addStars(float dt);
	void ThirdEnemyMove(Node *pSender, float, float);

	struct node {
		Sprite *sprite;
		int     life;
	};

	unsigned int effectplayedid;//背景乐意播放id

	Label *m_messageLabel = NULL;
	static Sprite *m_BossSprite;
	static int m_BossTotalLife;
	vector<node> m_enemyarray;

	int STARS_NUM = 0;
};

class WuJinSceneEnemyLayer :public EnemyLayer {
public:
	WuJinSceneEnemyLayer() {};
	~WuJinSceneEnemyLayer() {};

	CREATE_FUNC(WuJinSceneEnemyLayer);
};

class  FirstSceneEnemyLayer:public EnemyLayer
{
public:
	FirstSceneEnemyLayer() {};
	~FirstSceneEnemyLayer() {};

	CREATE_FUNC(FirstSceneEnemyLayer);

	void StartBossMode() { this->schedule(schedule_selector(FirstSceneEnemyLayer::CreateBoss), 95.0f); };

	void StartEnemyPlane() {
		float rdt = rand()%7+3;
		this->schedule(schedule_selector(FirstSceneEnemyLayer::CreateEnemyPlane), 1.0f);
		this->schedule(schedule_selector(FirstSceneEnemyLayer::CreateSecondEnemyPlane), rdt);
		this->schedule(schedule_selector(FirstSceneEnemyLayer::CreateThirdEnemyPlane), 10.0f);
		this->schedule(schedule_selector(FirstSceneEnemyLayer::CreateFourthEnemyPlane), 30.0);
	}
	//void CreateEnemyPlane(float dt);//创建普通敌机
	//virtual void CreateSecondEnemyPlane(float dt);//生产飞猪
	void CreateThirdEnemyPlane(float dt);//创建特殊敌机
	void CreateMissile(Node * pSender);
	void CreateBoss(float dt);
private:

};
class SecondSceneEnemyLayer :public EnemyLayer {
public:
	SecondSceneEnemyLayer() {};
	~SecondSceneEnemyLayer() {};

	CREATE_FUNC(SecondSceneEnemyLayer);

	void StartBossMode() { this->scheduleOnce(schedule_selector(EnemyLayer::CreateBoss), 5.0f); };

	void StartEnemyPlane() {
	};

	void CreateBossPlane(float dt);
private:

};

#endif // DEBUG

