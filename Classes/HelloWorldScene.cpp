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

    Vector<MenuItem*> items;
    auto item1 = MenuItemFont::create("resume", CC_CALLBACK_1(HelloWorld::resumeSchedule, this)); items.pushBack(item1);
    auto item2 = MenuItemFont::create("pause", CC_CALLBACK_1(HelloWorld::pauseSchedule, this)); items.pushBack(item2);

    for(auto item : items) item->setColor(Color3B::BLACK);

    auto menu = Menu::createWithArray(items);
    menu->alignItemsHorizontally(); menu->setPosition(Vec2(240, 80));

    auto man = Sprite::create("Images/grossini.png");
    man->setPosition(Vec2(100, 200));
    this->addChild(man);

    auto move = MoveBy::create(1.5f, Vec2(280, 0));
    auto back = move->reverse();
    auto action = Sequence::create(move, back, nullptr);

    man->runAction(RepeatForever::create(action));

    this->addChild(menu);


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

void HelloWorld::resumeSchedule(Ref* sender)
{
    Director::getInstance()->resume();
}

void HelloWorld::pauseSchedule(Ref* sender)
{
    Director::getInstance()->pause();
}
