#ifndef _BULLET_LAYER_
#define _BULLET_LAYER_

#include <GameScene.h>
#include<HelpTool.h>
#include<PlayerLayer.h>
#pragma once

class BulletLayer :public Layer
{
public:
	BulletLayer() { m_firstbullet = false; m_secondbullet = false; }
	~BulletLayer() {}
	virtual bool init();
	virtual void AddBullet(float dt);
	void RemoveBullet(Node* pSender);
	void StartShoot();
	void StopShoot() { this->unschedule(schedule_selector(BulletLayer::AddBullet)); };
	void SetOneRedBullet() { m_firstbullet = true; m_secondbullet = false; }
	void SetTwoBlueBullet() { m_secondbullet = true; m_firstbullet = false; }
	CREATE_FUNC(BulletLayer);

	static const int m_speed = 350;
	bool m_firstbullet;
	bool m_secondbullet;
	int m_bulletNum;
	Vec2 m_startpos;
	vector<Sprite*> m_bullet;
};

class FirstBulletLayer:public BulletLayer {
public:
	FirstBulletLayer() {};
	~FirstBulletLayer() {};
	CREATE_FUNC(FirstBulletLayer);
	virtual void AddBullet(float dt);
};

class SecondBulletLayer :public BulletLayer {
public:
	SecondBulletLayer(){};
	~SecondBulletLayer() {};
	CREATE_FUNC(SecondBulletLayer);
};

class ThirdBulletLayer :public BulletLayer {
public:
	ThirdBulletLayer() {};
	~ThirdBulletLayer() {};
	CREATE_FUNC(ThirdBulletLayer);
};

#endif