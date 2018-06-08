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

	//创建玩家飞机
	virtual void CreatePlayerPlane();

	//设置玩家飞机的精灵
	int SetPlayerPlaneSprite(Sprite *pSender) {
		if (playerPlaneSprite = pSender)
			return 1;
		return 0;
	}
	//取得玩家飞机的精灵
	Sprite * GetPlayerPlaneSprite() { return playerPlaneSprite; }
	//设置玩家飞机透明度实现渐变效果
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