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
        // left�������ز��������С����Ļ��ȵ�һ�룬˵�����ط���������
        if (p.x <= winSize.width / 2) {
            _activityJoystick(p);
        } else {
            // right������������������������������ź�
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

    // ����ô��ص���������������ģ�����������������
    if (start.x > winSize.width / 2) {
        return;
    }

    Point p = t->getLocation();
    // ��ȡλ�Ƶ�����ʼ���ƫ������ֱ�߾��룩
    float distance = start.getDistance(p);
    // ��ȡ��ʼ�㵽λ�Ƶ����������λΪ1�����꣩
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
    // �ԡ�ҡ�˻�������Բ��Ϊ�������ο�����ҡ�ˡ�����Ӧ�ı���
    Point start = _joystick_bg->getPosition();

    if (distance < 32) {
        // ����ƶ�δ������ҡ�˻���������ҡ�ˡ��ڡ���������ƫ��
        _joystick->setPosition(start + (direction * distance));
    } else if (distance > 96) {
        // ����ƶ�������ҡ�˻���������ҡ�ˡ�Բ��ʼ���ڡ���������Ե��ƫ��
        _joystick->setPosition(start + (direction * 64));
    } else {
        // ����ƶ�������ҡ�˻���������ҡ�ˡ���Եʼ���ڡ���������Ե��ƫ��
        _joystick->setPosition(start + (direction * 32));
    }
}
*/