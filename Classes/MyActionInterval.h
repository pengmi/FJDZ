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
	//确定一个椭圆的条件，需要知道空间位置（中心点坐标）、
	//长半轴（a）、和短半轴（b）（或者知道半焦距（c））。
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

static inline float tuoyuanXat(float a, float bx, float c, float t)//返回X坐标
{
	//参数方程
	return -a*cos(2 * M_PI*t) + a;
}
static inline float tuoyuanYat(float a, float by, float c, float t)//返回Y坐标
{
	float b = sqrt(powf(a, 2) - powf(c, 2));//因为之前定义的参数是焦距c而不是短半轴b，所以需要计算出b
											//参数方程
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


