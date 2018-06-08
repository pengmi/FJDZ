#ifndef _HELPTOOL_H_
#define _HELPTOOL_H_

#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <vector>
using namespace std;
#pragma once
#include "cocos2d.h"


class HelpTool  {
public:
	HelpTool() {};
	~HelpTool() {};

	static CCAnimation* CreateAnimationByFile(const char*name, int hori, int vert);
	static Rect GetSpritePosition(Sprite* sprite);//ȡ�þ���ķ���
	static SpriteFrameCache* GetFrameCache(const char*, const char*);
	static Animation* GetHitAnimationByFileName(const char*name,const char*,int );
	static int RemoveFromArry(vector< Sprite*>,Sprite*);
	static Sprite* GetSpriteByFileName(const char*,int);//�����Ҫ��������ȡpng��ֻ������Ԫ�ص�
};

#endif _HELPTOOL_H