#ifndef _MY_ACTION_INTERVAL_H_ 

#define _MY_ACTION_INTERVAL_H_ 

#pragma once

#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <vector>
using namespace std;

typedef struct _myEllipsesConfig {
	//ȷ��һ����Բ����������Ҫ֪���ռ�λ�ã����ĵ����꣩��
	//�����ᣨa�����Ͷ̰��ᣨb��������֪���뽹�ࣨc������
	Point centerPosition;
	float aLength;
	float cLength;
	int LeftOrRight=0;//0 or 1
}MyEllipsesConfig;


class MyEllipsesBy:public CCActionInterval
{
public:
	MyEllipsesBy() {};
	~MyEllipsesBy() {};

	//duration time ,config
	virtual bool initWithDuration(float ,const MyEllipsesConfig&);
	virtual void update(float dt);

	static MyEllipsesBy *Create(float,const MyEllipsesConfig&);
	
	MyEllipsesConfig m_sConfig;
	Point m_startPosition;
	Point s_startPosition;
private:
};

static inline float tuoyuanXat(float a, float bx, float c, float t)//����X����
{
	//��������
	return -a*cos(2 * M_PI*t) + a;
}
static inline float tuoyuanYat(float a, float by, float c, float t)//����Y����
{
	float b = sqrt(powf(a, 2) - powf(c, 2));//��Ϊ֮ǰ����Ĳ����ǽ���c�����Ƕ̰���b��������Ҫ�����b
											//��������
	return b*sin(2 * M_PI*t);
}


class MySpecialEllipsesBy :public MyEllipsesBy
{
public:
	MySpecialEllipsesBy() {};
	~MySpecialEllipsesBy() {};

	//duration time ,config
	//virtual bool initWithDuration(float, const MyEllipsesConfig&);
	virtual void update(float dt);

	static MySpecialEllipsesBy *Create(float, const MyEllipsesConfig&);
private:
};

#endif // !


