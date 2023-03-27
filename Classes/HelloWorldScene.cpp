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

    auto wlayer = LayerColor::create(Color4B(125, 125, 125, 255));
    this->addChild(wlayer);

    auto pMenuItem1 = MenuItemFont::create(
        " generate ",
        CC_CALLBACK_1(HelloWorld::doClick1, this)
    );

    pMenuItem1->setColor(Color3B::BLACK);

    auto pMenuItem2 = MenuItemFont::create(
        " remove ",
        CC_CALLBACK_1(HelloWorld::doClick1, this)
    );
    pMenuItem2->setColor(Color3B::BLACK);

    pMenuItem1->setTag(1);
    pMenuItem2->setTag(2);

    auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);

    pMenu->alignItemsVertically();
    this->addChild(pMenu);

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

void HelloWorld::doClick1(Ref* pSender) {
    auto item = (MenuItem*) pSender;
    int tag = item->getTag();

    if (tag == 1) {
        auto pMan = Sprite::create("Images/grossini.png");

        pMan->setPosition(Vec2(100, 160));
        pMan->setTag(11);
        this->addChild(pMan);
    }
    else {
        auto pMan = (Sprite*)getChildByTag(11);

        this->removeChild(pMan);
    }
    return;
}

void HelloWorld::doClick2(Ref* pSender) {
    // do sth
    log("do click 2");
    return;
}
