#include <MyActionInterval.h>

//
//MyEllipsesBy
//
MyEllipsesBy* MyEllipsesBy::Create(float t, const MyEllipsesConfig& c)//利用之前定义的椭圆的三个参数初始化椭圆
{
	MyEllipsesBy *pTuoyuanBy = new MyEllipsesBy();
	pTuoyuanBy->initWithDuration(t, c);
	pTuoyuanBy->autorelease();

	return pTuoyuanBy;
}

bool MyEllipsesBy::initWithDuration(float t, const MyEllipsesConfig& c)
{
	if (CCActionInterval::initWithDuration(t))
	{
		m_sConfig = c;
		return true;
	}

	return false;
}
void MyEllipsesBy::update(float time)
{
	//_target继承自CCAction.h,具体意义为实例
	if (_target)
	{
		CCPoint s_startPosition = m_sConfig.centerPosition;//中心点坐标
		float a = m_sConfig.aLength;
		float bx = m_sConfig.centerPosition.x;
		float by = m_sConfig.centerPosition.y;
		float c = m_sConfig.cLength;
		float x = tuoyuanXat(a, bx, c, time);//调用之前的坐标计算函数来计算出坐标值
		float y = tuoyuanYat(a, by, c, time);
		
		//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标
		_target->setPosition(ccpAdd(s_startPosition, ccp(x - a, y)));
	}
}

void MySpecialEllipsesBy::update(float time)
{
	//_target继承自CCAction.h,具体意义为实例
	if (_target)
	{
		CCPoint s_startPosition = m_sConfig.centerPosition;//中心点坐标
		float a = m_sConfig.aLength;
		float bx = m_sConfig.centerPosition.x;
		float by = m_sConfig.centerPosition.y;
		float c = m_sConfig.cLength;
		////////
		int leftOrRight = m_sConfig.LeftOrRight%2;
		float x = tuoyuanXat(a, bx, c, time);//调用之前的坐标计算函数来计算出坐标值
		if (leftOrRight==0)
		{
			x = tuoyuanXat(a, bx, c, time);
		}
		else
		{
			x = 0-x;
		}
		
		float y = tuoyuanYat(a, by, c, time);

		//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标
		_target->setPosition(ccpAdd(s_startPosition, ccp(x - a, y)));

		m_sConfig.centerPosition.y = s_startPosition.y - 4;
	}
}

MySpecialEllipsesBy * MySpecialEllipsesBy::Create(float t, const MyEllipsesConfig& c)
{
	MySpecialEllipsesBy *pTuoyuanBy = new MySpecialEllipsesBy();
	pTuoyuanBy->initWithDuration(t, c);
	pTuoyuanBy->autorelease();

	return pTuoyuanBy;
}
