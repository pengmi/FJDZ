#ifndef _PAUSELAYER_H
#define _PAUSELAYER_H
#include "cocos2d.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class PauseLayer:public Layer
{
public:
	PauseLayer(){}
	~PauseLayer(){}
	static Scene* scene(){
		Scene *scene=Scene::create();
		PauseLayer *layer=PauseLayer::create();
		scene->addChild(layer);
		return scene;
	}
	CREATE_FUNC(PauseLayer);
	virtual bool init(){
		if(Layer::init()==false)
			return false;
		Size size=Director::getInstance()->getVisibleSize();
		Vec2 origin=Director::getInstance()->getVisibleOrigin();
		auto sprite=Sprite::create("gameover.png");
		sprite->setPosition(ccp(origin.x+size.width/2,origin.y+size.height/2));
		this->addChild(sprite,1);

		auto menuitem=MenuItemImage::create(
			"ThunderNew/unipay_pic_refreshbg.png",
			"ThunderNew/unipay_pic_refreshbg_high.png",
			CC_CALLBACK_1(PauseLayer::menuResumeGame,this));
		menuitem->setPosition(ccp(origin.x,origin.y+50));
		auto menu=Menu::create(menuitem,NULL);
		this->addChild(menu,1);

		auto font=CCLabelBMFont::create("000","font/bitmapFontTest.fnt");
		font->setColor(ccc3(143,146,147));
		font->setPosition(ccp(origin.x+size.width/2,origin.y+size.height/2-30));
		CCString *strscore=CCString::createWithFormat("%d",GameScene::FiniteScore);
		font->setString(strscore->_string.c_str());
		this->addChild(font,1);
		return true;
	
	}
	//恢复游戏（实际是重开游戏）
	void menuResumeGame(Ref *psender){
		auto director=Director::getInstance();
		//Scene *pscene=GameScene::scene(1);
		Scene *pscene = HelloWorld::createScene();
		director->replaceScene(CCTransitionFade::create(3,pscene));
	}
};

#endif