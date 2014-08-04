#include "HeroLayer.h"

HeroLayer::HeroLayer()
{

}

HeroLayer::~HeroLayer()
{
}


bool HeroLayer::init()
{



//	bool ret = false;
//	do {
	//	CC_BREAK_IF( !Layer::init() );
		std::vector<std::string> searchbutto;
		searchbutto.push_back("Hero");
		CCFileUtils::getInstance()->setSearchPaths(searchbutto);
		CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("hero_idle.plist");

		hero= Sprite::createWithSpriteFrameName("hero_idle_00.png");//wrong
		hero->setPosition(Point(100,100));
		this->addChild(hero);

		Vector<SpriteFrame*>frameArray;

		char stra[50]={0};
		for (int l=0;l<4;l++)
		{
			sprintf(stra,"hero_idle_0%d.png",l);
			SpriteFrame *frame=   cache->spriteFrameByName(stra);
			frameArray.pushBack(frame);
		}

		Animation *trace=Animation::createWithSpriteFrames(frameArray,0.2f);//????

				hero->runAction(RepeatForever::create(Animate::create(trace)));
	
//	ret = true;
//
//	} while(false);

//	return ret;



	return true;
}

void HeroLayer::hero_run(){
  


	return;

}