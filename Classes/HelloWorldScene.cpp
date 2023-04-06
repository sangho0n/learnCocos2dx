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
    pManInitPos = Vec2(50, 220);
    pGirlInitPos = Vec2(50, 100);
    MenuItemFont::setFontSize(13);

    pMan = nullptr;
    pGirl = nullptr;
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
    pGirl = Sprite::create("Images/grossinis_sister1.png");
    pMan->setPosition(pManInitPos);
    pGirl->setPosition(pGirlInitPos);
    this->addChild(pMan); this->addChild(pGirl);


    // action 실행 및 원상복귀 메뉴
    cocos2d::Vector<MenuItem*> items;
    auto sequenceItem = MenuItemFont::create(" moveAndScaleUp ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(sequenceItem);
    auto spawnItem = MenuItemFont::create(" moveWhileScaleUp ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(spawnItem);
    auto repeatItem = MenuItemFont::create(" rotTwice ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(repeatItem);
    auto repeatForeverItem = MenuItemFont::create(" rotForever ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(repeatForeverItem);
    auto delayItem = MenuItemFont::create(" rotAfter2s ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(delayItem);
    auto resetItem = MenuItemFont::create(" reset ", CC_CALLBACK_1(HelloWorld::doOrUndo, this)); items.pushBack(resetItem);

    sequenceItem->setTag(SEQUENCE);
    spawnItem->setTag(SPAWN);
    repeatItem->setTag(REPEAT);
    repeatForeverItem->setTag(REPEAT_FOREVER);
    delayItem->setTag(DELAY);
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

    COMPOSE_ACTION action = (COMPOSE_ACTION) item->getTag();

    //enum COMPOSE_ACTION
    //{
    //    SEQUENCE,
    //    SPAWN,
    //    REPEAT,
    //    REPEAT_FOREVER,
    //    DELAY,
    //    RESET
    //};
    if (action == RESET) {
        reInitSprite();
        return;
    }

    auto move = MoveBy::create(1.0f, Vec2(100, 0));
    auto scale = ScaleBy::create(1.0f, 2.0f);
    auto rotate = RotateBy::create(1.0f, 90.0f);

    if (action == SEQUENCE) {
        auto seq = Sequence::create(move, scale, CallFunc::create(CC_CALLBACK_0(HelloWorld::reInitSpriteWithSender, this, pMan)), nullptr);
        pMan->runAction(seq);
        return;
    }
    if (action == SPAWN) {
        auto sp = Spawn::create(move, scale, nullptr);
        pMan->runAction(sp);
        return;
    }
    if (action == REPEAT) {
        auto rp = Repeat::create(rotate, 2);
        pMan->runAction(rp);
        return;
    }
    if (action == REPEAT_FOREVER) {
        auto rpf = RepeatForever::create(rotate); 
        pMan->runAction(rpf);
        return;
    }
    if(action == DELAY){
        auto del = DelayTime::create(2.0f);
        auto seq = Sequence::create(del, rotate, CallFunc::create(CC_CALLBACK_0(HelloWorld::reInitSpriteWithSender, this, pMan)), nullptr);
        pMan->runAction(seq);
        return;
    }
}

void HelloWorld::reInitSprite() {
    pMan->removeFromParentAndCleanup(true);
    pGirl->removeFromParentAndCleanup(true);
    pMan = Sprite::create("Images/grossini.png");
    pGirl = Sprite::create("Images/grossinis_sister1.png");
    pMan->setPosition(pManInitPos);
    pGirl->setPosition(pGirlInitPos);
    this->addChild(pMan);
    this->addChild(pGirl);
}

void HelloWorld::reInitSpriteWithSender(Ref* sender) {
    auto sprite = (Sprite*)sender;

    auto newSprite = Sprite::create(sprite->getResourceName());
    this->addChild(newSprite);
    if (newSprite->getResourceName().find("sister") != std::string::npos) {
        newSprite->setPosition(pGirlInitPos);
        pGirl->removeFromParentAndCleanup(true);
        pGirl = newSprite;
    }
    else {
        newSprite->setPosition(pManInitPos);
        pMan->removeFromParentAndCleanup(true);
        pMan = newSprite;
    }

    sprite->removeFromParent();
}
