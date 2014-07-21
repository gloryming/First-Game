/*#include "ActionSprite.h"
class Hero :public ActionSprite
{
public:
	Hero(void);
	~Hero(void);

	CREATE_FUNC(Hero);

	virtual bool init();
};*/
#include "cocos2d.h"
#include "BaseSprite.h"

class Hero : public BaseSprite
{
public:
	Hero();
	~Hero();

	bool init();

	CREATE_FUNC(Hero);

	std::function<void(cocos2d::Point, float)> walk;
	std::function<void(void)> stop;
};

