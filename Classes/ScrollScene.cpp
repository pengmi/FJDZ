#include <ScrollScene.h>
#include <cocos2d.h>

void ScrollScene::setBackgroud(Sprite * sprite,Sprite* selectpoint,Animation* animation)
{
	sprite->setPosition(0,0);
	auto contentsize = sprite->getContentSize();
	sprite->setScaleY(0.8f);
	float scalenum = (Director::getInstance()->getVisibleSize().width) / contentsize.width;
	sprite->setScaleX(scalenum);
	//this->setContentSize(contentsize);
	WINDOW_WIDTH = contentsize.width;
	WINDOW_HEIGHT = contentsize.height;
	this->setContentSize(Size(WINDOW_WIDTH*scalenum,WINDOW_HEIGHT));

	//Sprite* selectpoint = Sprite::create("ThunderNew/points003.png");
	selectpoint->setPosition(0,0);
	auto move1 =RepeatForever::create(RotateBy::create(4.0f,360));
	selectpoint->runAction(move1);
	
	auto animate = Animate::create(animation);
	auto move2 = RepeatForever::create(animate);

	selectpoint->runAction(RepeatForever::create(move2));

	this->addChild(sprite,0,BG_TAG);
	this->addChild(selectpoint,0,CHOOSE_SPTITE_TAG);
}

void ScrollScene::addNode(Node * level)
{
	if (level)
	{
		level->setPosition(Point(WINDOW_WIDTH/2 * (pageNode), 0));
		this->addChild(level);
		playerArr.push_back((Sprite*)level);
		pageNode++;
		level->setOpacity(100);
		level->setScale(1.2f);
		if (pageNode==1)
		{
			level->setScale(1.5f);
			level->setOpacity(255);
			curPageNode = 1;
			curSprite = (Sprite* )level;
		}
	}

}


bool ScrollScene::onTouchBegan(Touch *touch, Event  *event)
{
	touchDownPoint = touch->getLocation();
	touchCurPoint = touchDownPoint;

	auto contentsize = Director::getInstance()->getVisibleSize();
	auto contenorigion = Director::getInstance()->getVisibleOrigin();

	Rect touchrect;
	touchrect.origin.x = touchCurPoint.x;
	touchrect.origin.y = touchCurPoint.y;
	touchrect.size.width = 2;
	touchrect.size.height = 2;

	auto bgrect = this->boundingBox();
	/*在这里，bgrect得到的一个碰撞盒子，这个盒子的原点在精灵的正中央,
	所以，需要做一个偏移，让整个可见的层都能够被触碰到，而不会产生错误。所以在上面的setBackgroud
	里面，首先，应该把层的大小设置了。正常的一个层，应该是和屏幕一样大的。思想和HelpTool:GetSpritePosition()一样*/
	bgrect.origin.x = 0;
	bgrect.origin.y = bgrect.origin.y - WINDOW_HEIGHT / 2;


	if (touchrect.intersectsRect(bgrect))
	{
		m_shutdown = true;
	}

	return true;
}

void ScrollScene::onTouchMoved(Touch *touch, Event  *event)
{

	if (m_shutdown!=true)
	{
		return;
	}
	int index = 1;
	Point touchPoint = touch->getLocation();
	auto dis = fabsf(touchPoint.x - touchCurPoint.x);

	if (dis >= SHORTEST_SLIDE_LENGTH) 
	{
		float arc = 0;
		if (touchPoint.x - touchCurPoint.x>0 && curPageNode != 1)
		{
			curPageNode--;
			arc = WINDOW_WIDTH / 2;
		}
		else if (touchPoint.x - touchCurPoint.x<0 && curPageNode != pageNode)
		{
			curPageNode++;
			arc = -WINDOW_WIDTH / 2;
		}
		m_shutdown = false;

		SimpleAudioEngine::sharedEngine()->playEffect("sound/equip.mp3");

		for (vector<Node*>::iterator it = playerArr.begin(); it != playerArr.end(); it++)
		{
			if (index==curPageNode)
			{
				(*it)->setScale(1.5f);
			}
			(*it)->setScale(1.0f);
			(*it)->setOpacity(255);
			(*it)->runAction(MoveBy::create(0.4f, Point(arc, 0)));
			index++;
		}

	}
	touchCurPoint = touchPoint;

}

void ScrollScene::onTouchEnded(Touch *touch, Event  *event)
{
	int index = 1;
	for (vector<Node*>::iterator it = playerArr.begin(); it != playerArr.end(); it++)
	{
		if (index==curPageNode)
		{
			(*it)->setScale(1.5f);
			(*it)->setOpacity(255);
		}
		else
		{
			(*it)->setOpacity(100);
		}
		index++;
	}
	m_shutdown = false;
}

int ScrollScene::getCurPageNode()
{
	return curPageNode;
}

