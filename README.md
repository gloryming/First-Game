  第一个游戏-横版过关
==========

第一个游戏为横版过关游戏，通过8次练习，教会大家如何用Cocos2d-x制作一个完整的横版过关游戏。

`注意`:此文件仅由gloryming修改和更新。

项目安排及说明：本仓库共5名成员，每名成员在根目录下新建一个以自己名字命名的文件夹，文件夹里面存放各自的项目文件。所有项目图片资源都在`src`文件夹里面，每次任务更新一次资源。

##任务一：准备工作

任务目标：

- 创建一个横屏的Coco2d-x项目，命名为PompaDroid
- 拼出游戏主界面效果图如下

![task1](src/task1.png)

- 分辨率适配，适配所有移动设备分辨率（较难）
- 使用Tile Map绘制游戏地图

##任务二：让主角走路

任务目标：

- 添加控制方向的虚拟手柄
- 添加主角并能通过手柄控制其移动
- 主角不走路的时候有原地抖动的效果

`提示：`

那么现在我们该做些什么呢，你已经有了一个英雄和一个D-pad了。这就是本章所有内容？本章叫做“像这样动起来”，因为我们的最终目标是让英雄在地图上走动。准备好本章最后的延展内容。英雄要动起来第一步就是得为他创建一个运动的状态。为实现移动而创建动画动作的过程与创建闲置动哈动作的过程非常相似。实际上，其他所有的动作都是按这么个步骤来实现的。为了避免一遍遍的重新输入相同的代码，拥有一种工厂方法来生产动画会更好。你已经在之前声明了一个了，现在是时候来实现它了：

切换到ActionSprite.cpp并增加下列代码：

```
Animation* ActionSprite::animationWithPrefix(std::string prefix, int startFrameIdx, int frameCount, float delay){
int idxCount = frameCount + startFrameIdx;
Vector<SpriteFrame*> frames;
char name[50];
SpriteFrame* frame;
for (int i = startFrameIdx; i < idxCount; i++){
    sprintf(name, "%s_%02d.png", prefix.c_str(), i);
    frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
    frames.pushBack(frame);
}
return Animation::createWithSpriteFrames(frames,delay);
}
```

这个方法与你如何创建闲置动画非长类似。不同之处是它的参数使得这个方法变得可复用。

这个方法通过拥有prefix_XX（一个从起始帧的id开始并递增总帧数次的两位数）这样的格式的精灵帧来创建动画。有了这个方法，你就不再需要每次创建Vector和一个循环来创建动画了。 切换到Hero.cpp并且用下列代码替换掉init中的代码：

```
bool Hero::init(){
if (!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"))
{
        return false;
    }
    Animation* idleAnimation = animationWithPrefix("hero_idle",0,6,1.0/12.0);
    idleAction = RepeatForever::create(Animate::create(idleAnimation));

    Animation* walkAnimation = animationWithPrefix("hero_walk",0,8,1.0/12.0);
    walkAction = RepeatForever::create(Animate::create(walkAnimation));

    CC_SAFE_RETAIN(idleAction);
    CC_SAFE_RETAIN(walkAction);

    this->walkSpeed = 80 ;
    this->directionX = 1.0;
    this->centerToBottom = 39.0;
    this->centerToSides = 29.0;
    return true;
}
```

##任务三：让主角跑，跳，攻击

##任务四：待续

##任务五：待续

##任务六：待续

##任务七：待续

##任务八：待续