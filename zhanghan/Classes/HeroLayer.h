#ifndef __HEROLAYER_H__
#define __HEROLAYER_H__
#include "cocos2d.h"
#include "Play.h"

USING_NS_CC;



class HeroLayer : public cocos2d::Layer
{
public:
	HeroLayer(void);
	~HeroLayer(void);

	virtual bool init();

	CREATE_FUNC(HeroLayer);
	void hero_run();
	cocos2d::Sprite *hero;
   CC_SYNTHESIZE(HeroLayer*, m_pHero, HeroLayer);
private:
    bool heroinit;
	
};
#endif //__HEROLAYER_H__