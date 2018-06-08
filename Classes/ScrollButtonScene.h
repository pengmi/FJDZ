#ifndef __SCROLL_BUTTON_SCENE__
#define __SCROLL_BUTTON_SCENE__
#pragma once
#include <ScrollScene.h>

class ScrollButtonScene :public ScrollScene
{
	ScrollButtonScene() {
		pageNode = 0;
		curPageNode = 0;
		WINDOW_WIDTH = 0;
		WINDOW_HEIGHT = 0;
		m_shutdown = false;
	};
	~ScrollButtonScene(){};
public:
	CREATE_FUNC(ScrollButtonScene);
	//void addNode(Node* level);
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