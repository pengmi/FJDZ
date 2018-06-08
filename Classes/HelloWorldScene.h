#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#define CHAPTER_WUJIN 1
#define CHAPTER_BAIYANG 2
#define CHAPTER_JUXIE 3
#define CHAPTER_SHESHOU 4

#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <vector>
using namespace std;
#include <iostream>
#include <fstream>

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	//读取分数榜单文件
	int loadScoresFile(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartGameCallback(Ref *pSender);
	
	//bool onTouchBegan(Touch *touch, Event *user_event);
	//void onTouchMoved(Touch *pTouch, Event  *pEvent);
	//void onTouchEnded(Touch *pTouch, Event  *pEvent);

	//explosion 
	void startExplosion(float dt);
	void removeExplosion(Node *pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	class ScrollScene *scrollplayerlayer1;
	ScrollScene *scrollplayerlayer2;
	//ScrollButtonScene *scrollbuttonlayer;
	int PLAYER_SELECTED;
	int CHAPTER_SELECTED;
};

#endif // __HELLOWORLD_SCENE_H__
