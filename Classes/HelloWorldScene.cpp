/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::HelloWorld() {
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    // 씬 레이어 크기 지정
    auto wlayer = LayerColor::create(Color4B(125, 125, 125, 255));
    this->addChild(wlayer);

    // 스프라이트 생성 및 추가
    pMan = Sprite::create("Images/grossini.png");
    pMan->setPosition(Vec2(240, 160));
    this->addChild(pMan); 



    // atlas 애니메이션, plist 애니메이션
    auto atlasItem = MenuItemFont::create(" Atlas ", CC_CALLBACK_1(HelloWorld::atlasCallBack, this));

    auto plistItem = MenuItemFont::create(" Plist ", CC_CALLBACK_1(HelloWorld::plistCallBack, this));

    auto runMenu = Menu::create(atlasItem, plistItem, nullptr);
    runMenu->setPosition(Vec2(240, 80));
    runMenu->alignItemsHorizontally();
    this->addChild(runMenu);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void HelloWorld::atlasCallBack(Ref* sender) {
    auto animation = Animation::create(); animation->setDelayPerUnit(0.3f);
    // 디렉터를 이용해 텍스처를 만드는 방법. 이 방법을 쓰면, 스프라이트 생성 시 위에서 파일을 다시 한번 불러오지 않고도, 캐시에 저장되어있는 것을 활용할 수 있음
    auto texture = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");
    // 스프라이트를 통해 택스쳐를 만드는 방법
    //auto sprite = Sprite::create("Images/grossini_dance_atlas.png");
    //auto texture1 = sprite->getTexture();

    for (int i = 0; i < 14; i++) {
        int col = i % 5;
        int row = i / 5;

        animation->addSpriteFrameWithTexture(texture, Rect(col * 85, row * 121, 85, 121));
    }

    auto anim = Animate::create(animation);
    pMan->runAction(anim);
}

void HelloWorld::plistCallBack(Ref* sender) {
    auto cache = SpriteFrameCache::getInstance(); // singletone
    cache->addSpriteFramesWithFile("animations/grossini.plist");

    Vector<SpriteFrame*> animFrames;

    std::string str;
    for (int i = 1; i < 15; i++) {
        if (i < 10)
            str = ("grossini_dance_0" + std::to_string(i));
        else
            str = "grossini_dance_" + std::to_string(i);
        str += ".png";

        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }

    auto animation = Animation::createWithSpriteFrames(animFrames); animation->setDelayPerUnit(0.3f);
    auto animate = Animate::create(animation);
    pMan->runAction(animate);
}
