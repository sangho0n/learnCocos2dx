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

    // Sprite Frame Cache 

    auto sfcache = SpriteFrameCache::getInstance();

    sfcache->addSpriteFramesWithFile("animations/grossini_family.plist");
    sfcache->addSpriteFramesWithFile("animations/grossini.plist");
    auto pSprite = SpriteFrame::create("images/blocks9.png", Rect(0, 0, 96, 96));
    sfcache->addSpriteFrame(pSprite, "blocks9.png");

    auto pWoman = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
    pWoman->setPosition(Vec2(120, 220));

    auto pMan = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
    pMan->setPosition(Vec2(240, 220));

    auto pBox = Sprite::createWithSpriteFrameName("blocks9.png");
    pBox->setPosition(Vec2(360, 220));

    this->addChild(pWoman);
    this->addChild(pMan);
    this->addChild(pBox);

    // Texture Cache

    auto txCache = Director::getInstance()->getTextureCache();

    auto texture1 = txCache->addImage("animations/grossini_dance_atlas.png");
    auto texture2 = txCache->addImage("animations/dragon_animation.png");

    auto pMan2 = Sprite::createWithTexture(texture1, Rect(0, 0, 85, 121));
    pMan2->setPosition(Vec2(120, 100));

    auto pDragon = Sprite::createWithTexture(texture2, Rect(0, 0, 130, 140));
    pDragon->setPosition(Vec2(240, 100));

    txCache->addImageAsync("images/blocks9.png", CC_CALLBACK_1(HelloWorld::afterImgLoad, this));

    this->addChild(pMan2);
    this->addChild(pDragon);

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

void HelloWorld::afterImgLoad(Ref* pSender)
{
    auto tex = static_cast<Texture2D*>(pSender);
    auto sprite = Sprite::createWithTexture(tex);
    sprite->setPosition(Vec2(360, 100));
    this->addChild(sprite);
}
