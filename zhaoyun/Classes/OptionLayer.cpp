#include "OptionLayer.h"
#include "SimpleDPadSprite.h"

OptionLayer::OptionLayer()
{
	this->setDPad(NULL);
}

OptionLayer::~OptionLayer()
{}

bool OptionLayer::init()
{
	if (!Layer::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dPad.plist");
	_dPads = SpriteBatchNode::create("dPad.pvr.ccz");
	_dPads->getTexture()->setAliasTexParameters();
	this->addChild(_dPads,0);
	_dPad = SimpleDPad::dPadWithSpriteFrameName(__String::create("dpad_center@2x.png"), 64);
	_dPad->setPosition(ccp(64.0, 64.0));
	_dPad->setOpacity(100);
	this->addChild(_dPad);

	return true;
}

/*void OptionLayer::onTouchesBegan(Set *ts, Event *e)
{
    Size winSize = Director::getInstance()->getWinSize();
    SetIterator iter = ts->begin();

    while (iter != ts->end()) {
        Touch *t = (Touch*)(*iter);
        Point p = t->getLocation();
        // left，当触控操作的起点小于屏幕宽度的一半，说明触控发生在左屏
        if (p.x <= winSize.width / 2) {
            _activityJoystick(p);
        } else {
            // right，否则发生在右屏，会产生“攻击”信号
            _delegator->onAttack();
        }

        iter++;
    }
}

void OptionLayer::onTouchesMoved(Set *ts, Event *e)
{
    Size winSize = Director::getInstance()->getWinSize();
    SetIterator iter = ts->begin();
    Touch *t = (Touch*)(*iter);
    Point start = t->getStartLocation();

    // 如果该触控的起点是右屏产生的，则不做“滑动”处理
    if (start.x > winSize.width / 2) {
        return;
    }

    Point p = t->getLocation();
    // 获取位移点与起始点的偏移量（直线距离）
    float distance = start.getDistance(p);
    // 获取起始点到位移点的向量（单位为1的坐标）
	Point direction;
	direction.x=(p.x-start.x)/sqrt((p.x-start.x)*(p.x-start.x)+(p.y-start.y)*(p.y-start.y));
	direction.y=(p.y-start.y)/sqrt((p.x-start.x)*(p.x-start.x)+(p.y-start.y)*(p.y-start.y));
    Point direction = (p - start).getNormalized();

    _updateJoystick(direction, distance);
    _delegator->onWalk(direction, distance);
}

void OptionLayer::onTouchesEnded(Set *ts, Event *e)
{
    if (_joystick_bg->isVisible()) {
        _inactivityJoystick();
        _delegator->onStop();
    }
}

void OptionLayer::_activityJoystick(Point position)
{
    _joystick->setPosition(position);
    _joystick_bg->setPosition(position);
    _joystick->setVisible(true);
    _joystick_bg->setVisible(true);
}

void OptionLayer::_inactivityJoystick()
{
    _joystick->setPosition(_joystick_bg->getPosition());
    _joystick->setVisible(false);
    _joystick_bg->setVisible(false);
}

void OptionLayer::_updateJoystick(Point direction, float distance)
{
    // 以“摇杆基座”的圆心为触控起点参考，“摇杆”做相应的便宜
    Point start = _joystick_bg->getPosition();

    if (distance < 32) {
        // 如果移动未超出“摇杆基座”，“摇杆”在“基座”做偏移
        _joystick->setPosition(start + (direction * distance));
    } else if (distance > 96) {
        // 如果移动超出“摇杆基座”，“摇杆”圆心始终在“基座”边缘做偏移
        _joystick->setPosition(start + (direction * 64));
    } else {
        // 如果移动超出“摇杆基座”，“摇杆”边缘始终在“基座”边缘做偏移
        _joystick->setPosition(start + (direction * 32));
    }
}
*/