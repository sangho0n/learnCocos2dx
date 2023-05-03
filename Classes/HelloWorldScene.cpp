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

    auto wlayer = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(wlayer);

    p1 = Sprite::create("Images/grossinis_sister1.png");
    p2 = Sprite::create("Images/grossinis_sister2.png");

    Vector<MenuItem*> items;
    MenuItemFont::setFontSize(15); // static font size change method
    auto item1 = MenuItemFont::create("radial", CC_CALLBACK_1(HelloWorld::radial, this)); items.pushBack(item1);
    auto item2 = MenuItemFont::create("horizontal", CC_CALLBACK_1(HelloWorld::horizontal, this)); items.pushBack(item2); 
    auto item3 = MenuItemFont::create("vertical", CC_CALLBACK_1(HelloWorld::vertical, this)); items.pushBack(item3); 
    auto item4 = MenuItemFont::create("changeRate", CC_CALLBACK_1(HelloWorld::changeRate, this)); items.pushBack(item4);
    auto item5 = MenuItemFont::create("withAction", CC_CALLBACK_1(HelloWorld::withAction, this)); items.pushBack(item5);

    for (auto item : items) { item->setColor(Color3B::BLACK); }

    auto menu = Menu::createWithArray(items);
    menu->alignItemsHorizontally(); menu->setPosition(Vec2(240, 80));

    this->addChild(menu);
    this->addChild(p1); p1->setVisible(false);
    this->addChild(p2); p2->setVisible(false);
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

void HelloWorld::radial(Ref* sender)
{
    auto to1 = ProgressTo::create(1.0f, 100.0f);
    auto to2 = ProgressTo::create(1.0f, 100.0f);
    auto reset = ProgressTo::create(0.0f, 0.0f);
    auto seq1 = Sequence::createWithTwoActions(to1, reset->clone());
    auto seq2 = Sequence::createWithTwoActions(to2, reset->clone());

    // CC
    t1 = ProgressTimer::create(p1);
    t1->setType(ProgressTimer::Type::RADIAL);
    t1->setPosition(Vec2(140, 160));
    addChild(t1);

    // CCW
    t2 = ProgressTimer::create(p2);
    t2->setType(ProgressTimer::Type::RADIAL);
    t2->setPosition(Vec2(340, 160));
    t2->setReverseDirection(true);
    addChild(t2);

    t1->runAction(seq1);
    t2->runAction(seq2);
}

void HelloWorld::horizontal(Ref* sender)
{

}

void HelloWorld::vertical(Ref* sender)
{

}

void HelloWorld::changeRate(Ref* sender)
{

}

void HelloWorld::withAction(Ref* sender)
{

}
