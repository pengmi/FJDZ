#ifndef _GAMESCENE_H
#define _GAMESCENE_H

#include<EnemyLayer.h>
#include<OtherItem.h>
#include <PlayerLayer.h>
#include<BulletLayer.h>
#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <vector>
using namespace std;
#pragma once
#include "cocos2d.h"

#define PlaneLayerZOrder 10
#define EnemyLayerZOrder 8
#define PlayerBulletLayerZOrder 9
#define BossBulletLayerZOrder 11
#define LaserLayerZOrder 15
#define PlaneNum         10001 //���
#define PlaneEffectNum   10002  //β�����Ч��
#define ZhaDanTag            200 //ը����ǣ�������ȡͼ�꾫��
#define DiamondCounterTag 20001 //��ʯ����
#define DiamondTag        20002//��ʯ���
#define PlayerLaserMainTag    20003 //���� 20003-20007��Ҫ��ռ��
#define SceneBaiYangKillTagOne   20008
#define SceneBaiYangKillTagTwo   20009
#define StarsPlaneTag            20010
#define JuXieStarsTag            20015
#define LittlePlane      0
#define BigPlane         1
#define MorePlane        2
#define Bomb             3
#define Boss			 4
#define Pig				5
#define Missile			6
#define Killer			7
//#define PlayerLife		 1
#define LittlePlaneLife  1
#define BigPlaneLife     15
#define MorePlaneLife    100
#define BombLife         50
#define BossLife		 5000
#define PigLife			 70
#define	MissileLife		 5
#define KillerLife       80
#define SceneBaiYangKillerLife 200
#define SceneBaiYangKillerMissileLife 10
#define SceneJuXieStarsLife 1
#define LittlePlaneScore 2
#define BigPlaneScore    5
#define MoreBigPlaneScore 10
#define BombScore        5
#define BossScore        100
#define PigScore         10
#define	MissileScore	 5
#define KillerScore		5
#define JuXieStarsScore  1
#define ZhaDan	1		//������ʾ����һ�ֵ���
#define ShuangZidan 2	//
#define Life 3			//
/*�ɻ����*/
#define FIRST_PLANE 101011
#define SECOND_PLANE 101012
#define THIRD_PLANE 101013



class GameScene :
	public Layer
{
public:
	friend class BulletLayer;
	friend class EnemyLayer;
	friend class BossEnemyBulletLayer;

	GameScene(void);
	~GameScene(void);
	static GameScene* create(int playerselected) {
		GameScene *pRet = new GameScene;
		if (pRet&&pRet->init(playerselected+101010))
		{
			/*��һҳ�洫���ֵ*/
			pRet->PLAYER_SELECTED = (playerselected + 101010);
			pRet->autorelease();
			return pRet;
		}
		else {
			CC_SAFE_DELETE(pRet);
			return NULL;
		}
	};
	virtual bool init(int);
	static Scene* scene(int playerselected){
		Scene *scene=Scene::create();
		GameScene *layer=GameScene::create(playerselected);
		scene->addChild(layer);


		return scene;
	}
//	CREATE_FUNC(GameScene);
	virtual void setBackground();
	virtual void setLayer();
	void backgroundmove(float dt);
	void LaserMove(float dt);
	int GetPlayerSelected();
	void update(float dt);
	void AnimationPlane(Sprite*);
	void AnimationHitPlane(Sprite*);
	void AnimationHitBoss(Sprite*,int);
	virtual void AnimationDestroyBoss(Sprite*);
	//�л���������������Ч
	void startHitExplosionAnimation(Sprite *sprite);
	//�л���ը�Ժ�������ʯ
	void startDestroyedMode(Node *pSender);
	//��ʯ����
	void diamondFall(Node *pSender);
	void removeExplosionAnimation(Node *psender);

	void removeDiamond(Node *psender);
	void removePlane(Node *psender);
	void removeMissile(Node * pSender);
	void removeUfo(Node *psender);
	void removeBullet(Node *pSender);
	virtual void removeBoss(Node *pSender);
	void removePlayerLaser(float dt);
	//���boss�ӵ�������Ƿ���ײ
	int IfBossBulletintersects();

	void PlayerLifeCount();
	//Rect GetSpritePosition(Sprite*);
	virtual bool onTouchBegan(Touch *touch,Event *user_event);
	virtual void onTouchMoved(Touch *touch,Event *user_event);
	virtual void onTouchEnded(Touch *touch,Event *user_evenr);
	virtual void keyBackClicked(Touch *touch, Event *user_evenr);//Android ���ؼ�
	virtual void keyMenuClicked(Touch *touch, Event *user_evenr);//Android �˵���
	void menuPauseCallBack(Ref *pSender);
	static int FiniteScore;

	struct  diamondNode
	{
		Sprite* sprite=NULL;
		int score = 2;
	};
	
	Sprite* m_bk1;
	Sprite* m_bk2;
	class PlayerLayer *m_player;
	class BulletLayer *m_mybullet;
	class BossEnemyBulletLayer *m_bossBulletLayer;
	class EnemyLayer  *m_enemy;
	class UFOLayer    *m_ufo;
	bool    m_shutdown;
	int     m_score;
	int     m_diamondnum;
	LabelBMFont *m_font;

	vector<diamondNode> m_diamondArray;

	/*������һҳ�洫���ֵ*/
	int PLAYER_SELECTED;
	//int CHAPTER_SELECTED;
};

class WuJinGameScene :public GameScene {
public:
	WuJinGameScene() {};
	~WuJinGameScene() {};

	static WuJinGameScene* create(int playerselected) {
		WuJinGameScene *pRet = new WuJinGameScene;
		if (pRet&&pRet->init(playerselected + 101010))
		{
			/*��һҳ�洫���ֵ*/
			pRet->PLAYER_SELECTED = (playerselected + 101010);
			pRet->autorelease();
			return pRet;
		}
		else {
			CC_SAFE_DELETE(pRet);
			return NULL;
		}
	};

	static Scene* scene(int playerselected) {
		Scene *scene = Scene::create();
		WuJinGameScene *layer = WuJinGameScene::create(playerselected);
		scene->addChild(layer);


		return scene;
	};

	virtual void setBackground();
	void setLayer();
	//void AnimationDestroyBoss(Sprite*);

};

class BaiYangGameScene:public GameScene{
public:
	BaiYangGameScene() {};
	~BaiYangGameScene() {};

	static BaiYangGameScene* create(int playerselected) {
		BaiYangGameScene *pRet = new BaiYangGameScene;
		if (pRet&&pRet->init(playerselected + 101010))
		{
			/*��һҳ�洫���ֵ*/
			pRet->PLAYER_SELECTED = (playerselected + 101010);
			pRet->autorelease();
			return pRet;
		}
		else {
			CC_SAFE_DELETE(pRet);
			return NULL;
		}
	};

	static Scene* scene(int playerselected) {
		Scene *scene = Scene::create();
		BaiYangGameScene *layer = BaiYangGameScene::create(playerselected);
		scene->addChild(layer);


		return scene;
	}

	virtual void setBackground();
	void setLayer();
	//void AnimationDestroyBoss(Sprite*);
	void removeBoss(Node *pSender);
};

class JuXieGameScene :public GameScene {
public:
	JuXieGameScene() {};
	~JuXieGameScene() {};

	static JuXieGameScene* create(int playerselected) {
		JuXieGameScene *pRet = new JuXieGameScene;
		if (pRet&&pRet->init(playerselected + 101010))
		{
			/*��һҳ�洫���ֵ*/
			pRet->PLAYER_SELECTED = (playerselected + 101010);
			pRet->autorelease();
			return pRet;
		}
		else {
			CC_SAFE_DELETE(pRet);
			return NULL;
		}
	};

	static Scene* scene(int playerselected) {
		Scene *scene = Scene::create();
		JuXieGameScene *layer = JuXieGameScene::create(playerselected);
		scene->addChild(layer);


		return scene;
	}

	virtual void setBackground();
	void setLayer();
//	void AnimationDestroyBoss(Sprite*);
	void removeBoss(Node *pSender);
};


#endif
