#ifndef _PLAYER_LAYER_
#define _PLAYER_LAYER_

#include <GameScene.h>
#include<HelpTool.h>
#pragma once

class PlayerLayer :public Layer
{
public:
	PlayerLayer() {}
	~PlayerLayer() {}
	static PlayerLayer*  create();
	virtual bool init();
	static PlayerLayer *SharePlane() { return sharedPlane; }

	//������ҷɻ�
	virtual void CreatePlayerPlane();

	//������ҷɻ��ľ���
	int SetPlayerPlaneSprite(Sprite *pSender) {
		if (playerPlaneSprite = pSender)
			return 1;
		return 0;
	}
	//ȡ����ҷɻ��ľ���
	Sprite * GetPlayerPlaneSprite() { return playerPlaneSprite; }
	//������ҷɻ�͸����ʵ�ֽ���Ч��
	void SetPlayerSpriteOpacity(float dt);

	void AnimationPlayerPlane();

	static PlayerLayer *sharedPlane;
	Sprite *playerPlaneSprite = NULL;

};

class FirstPlayerLayer:public PlayerLayer
{
public:
	FirstPlayerLayer() {};
	~FirstPlayerLayer() {};
	static PlayerLayer*  create();
	void CreatePlayerPlane();
private:
	
};

class SecondPlayerLayer :public PlayerLayer
{
public:
	SecondPlayerLayer() {};
	~SecondPlayerLayer() {};
	static SecondPlayerLayer*  create();
	void CreatePlayerPlane();
private:

};

class ThirdPlayerLayer :public PlayerLayer
{
public:
	ThirdPlayerLayer() {};
	~ThirdPlayerLayer() {};
	static PlayerLayer*  create();
	void CreatePlayerPlane();
private:

};


#endif