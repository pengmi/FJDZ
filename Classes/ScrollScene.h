#ifndef __SCROLL_SCENE__
#define __SCROLL_SCENE__

#define SHORTEST_SLIDE_LENGTH 30
#define BG_TAG 10001
#define CHOOSE_SPTITE_TAG 20001

#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <vector>
using namespace std;
#include <HelpTool.h>
#pragma once

class ScrollScene : public Layer
{
public:
	ScrollScene() { 
		pageNode = 0;
		curPageNode = 0;
		WINDOW_WIDTH = 0;
		WINDOW_HEIGHT = 0;
		m_shutdown = false;
		///////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
	};
	~ScrollScene() {};

	//virtual bool init();
	//static cocos2d::Scene* createScene();
	CREATE_FUNC(ScrollScene);

	void setBackgroud(Sprite*,Sprite*,Animation *);
	virtual void addNode(Node* level);
	//virtual void menuCloseCallback(Ref* pSender);
	bool onTouchBegan(Touch *pTouch, Event  *pEvent);
	void onTouchMoved(Touch *pTouch, Event  *pEvent);
	void onTouchEnded(Touch *pTouch, Event  *pEvent);
	int getCurPageNode();
private:
	bool m_shutdown;
	vector<Node*> playerArr;
	int pageNode;
	int curPageNode;
	Sprite * curSprite;
	Point touchDownPoint;
	Point touchUpPoint;
	Point touchCurPoint;
	float WINDOW_WIDTH;
	float WINDOW_HEIGHT;
	
	
};



#endif 