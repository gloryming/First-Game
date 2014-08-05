#include "ActionSprite.h"
USING_NS_CC;

Animation * ActionSprite::animationWithPrefix(std::string prefix, int startFrameIdx, int frameCount, float delay)
{
		int idxCount = frameCount + startFrameIdx;
		auto animation = Animation::create();
		char name[50];
		for (int i = startFrameIdx; i < idxCount; i++){
			sprintf(name, "%s_%02d.png", prefix.c_str(), i);
			animation->addSpriteFrameWithFile(name);
		}
		animation->setDelayPerUnit(1.0f / 12);
		animation->setRestoreOriginalFrame(true);
		return animation;
}