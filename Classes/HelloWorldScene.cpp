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
    // 초기 위치 지정
    // default scene size 480, 320
    actionKindMenuPos = Vec2(240, 300);
    actionDoMenuPos = Vec2(400, 200);
    pBallInitPos = Vec2(50, 270);
    pManInitPos = Vec2(50, 200);
    pGirl1InitPos = Vec2(50, 120);
    pGirl2InitPos = Vec2(50, 30);
    MenuItemFont::setFontSize(13);

    pBall = nullptr;
    pMan = nullptr;
    pGirl1 = nullptr;
    pGirl2 = nullptr;
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
    pBall = Sprite::create("Images/ball.png");
    pMan = Sprite::create("Images/grossini.png");
    pGirl1 = Sprite::create("Images/grossinis_sister1.png");
    pGirl2 = Sprite::create("Images/grossinis_sister2.png");
    pBall->setPosition(pBallInitPos);
    pMan->setPosition(pManInitPos);
    pGirl1->setPosition(pGirl1InitPos);
    pGirl2->setPosition(pGirl2InitPos);
    pMan->setScale(0.5f);
    pGirl1->setScale(0.5f);
    pGirl2->setScale(0.5f);
    this->addChild(pBall); this->addChild(pMan);
    this->addChild(pGirl1); this->addChild(pGirl2);


    // action 실행 및 원상복귀 메뉴
    cocos2d::Vector<MenuItem*> items;
    auto easeItem = MenuItemFont::create(" EASE ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(easeItem);
    auto elasticeItem = MenuItemFont::create(" ELASTICE ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(elasticeItem);
    auto bounceItem = MenuItemFont::create(" BOUNCE ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(bounceItem);
    auto speedItem = MenuItemFont::create(" SPEED ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(speedItem);
    auto resetItem = MenuItemFont::create(" RESET ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(resetItem);

    easeItem->setTag(NORMAL);
    elasticeItem->setTag(ELASTIC);
    bounceItem->setTag(BOUNCE);
    speedItem->setTag(SPEED);
    resetItem->setTag(RESET);

    auto doOrUndoMenu = Menu::createWithArray(items);
    doOrUndoMenu->setPosition(actionDoMenuPos);
    doOrUndoMenu->alignItemsVertically();
    this->addChild(doOrUndoMenu);

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

void HelloWorld::doOrUndo(Ref* pSender) {
    auto item = (MenuItemFont*)pSender;

    EASE_ACTION action = (EASE_ACTION) item->getTag();

    //enum COMPOSE_ACTION
    //{
        //NORMAL,
        //ELASTIC,
        //BOUNCE,
        //SPEED,
        //RESET
    //};
    if (action == RESET) {
        pBall->removeFromParentAndCleanup(true);
        pMan->removeFromParentAndCleanup(true);
        pGirl1->removeFromParentAndCleanup(true);
        pGirl2->removeFromParentAndCleanup(true);
        pBall = Sprite::create("Images/ball.png");
        pMan = Sprite::create("Images/grossini.png");
        pGirl1 = Sprite::create("Images/grossinis_sister1.png");
        pGirl2 = Sprite::create("Images/grossinis_sister2.png");
        pBall->setPosition(pBallInitPos);
        pMan->setPosition(pManInitPos);
        pGirl1->setPosition(pGirl1InitPos);
        pGirl2->setPosition(pGirl2InitPos);
        pMan->setScale(0.5f);
        pGirl1->setScale(0.5f);
        pGirl2->setScale(0.5f);
        this->addChild(pBall);
        this->addChild(pMan);
        this->addChild(pGirl1);
        this->addChild(pGirl2);
        return;
    }

    auto move = MoveBy::create(1.0f, Vec2(100, 0));

    if (action == NORMAL) {

        return;
    }
    if (action == ELASTIC) {
        return;
    }
    if (action == BOUNCE) {
        
        return;
    }
    if (action == SPEED) {

        return;
    }
}
