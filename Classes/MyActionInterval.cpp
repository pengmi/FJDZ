#include <MyActionInterval.h>

//
//MyEllipsesBy
//
MyEllipsesBy* MyEllipsesBy::Create(float t, const MyEllipsesConfig& c)//����֮ǰ�������Բ������������ʼ����Բ
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
	//_target�̳���CCAction.h,��������Ϊʵ��
	if (_target)
	{
		CCPoint s_startPosition = m_sConfig.centerPosition;//���ĵ�����
		float a = m_sConfig.aLength;
		float bx = m_sConfig.centerPosition.x;
		float by = m_sConfig.centerPosition.y;
		float c = m_sConfig.cLength;
		float x = tuoyuanXat(a, bx, c, time);//����֮ǰ��������㺯�������������ֵ
		float y = tuoyuanYat(a, by, c, time);
		
		//�������ǻ����������Բ����ֵ����ԭ��Ϊ���ĵģ�������Ҫ���������趨�����ĵ�����
		_target->setPosition(ccpAdd(s_startPosition, ccp(x - a, y)));
	}
}

void MySpecialEllipsesBy::update(float time)
{
	//_target�̳���CCAction.h,��������Ϊʵ��
	if (_target)
	{
		CCPoint s_startPosition = m_sConfig.centerPosition;//���ĵ�����
		float a = m_sConfig.aLength;
		float bx = m_sConfig.centerPosition.x;
		float by = m_sConfig.centerPosition.y;
		float c = m_sConfig.cLength;
		////////
		int leftOrRight = m_sConfig.LeftOrRight%2;
		float x = tuoyuanXat(a, bx, c, time);//����֮ǰ��������㺯�������������ֵ
		if (leftOrRight==0)
		{
			x = tuoyuanXat(a, bx, c, time);
		}
		else
		{
			x = 0-x;
		}
		
		float y = tuoyuanYat(a, by, c, time);

		//�������ǻ����������Բ����ֵ����ԭ��Ϊ���ĵģ�������Ҫ���������趨�����ĵ�����
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
