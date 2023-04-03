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
    actionKind = " move ";
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

    // 스프라이트 생성 및 추가새
    pMan = Sprite::create("Images/grossini.png");
    pGirl = Sprite::create("Images/grossinis_sister1.png");
    pMan->setPosition(pManInitPos);
    pGirl->setPosition(pGirlInitPos);
    originColorMan = pMan->getColor();
    originColorGirl = pGirl->getColor();
    this->addChild(pMan); this->addChild(pGirl);

    // action 종류 선택 메뉴
    auto moveActionItem = MenuItemFont::create(" move ", CC_CALLBACK_1(HelloWorld::actionKindChange, this)); moveActionItem->setColor(Color3B::BLACK);
    auto jumpActionItem = MenuItemFont::create(" jump ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto bezierActionItem = MenuItemFont::create(" bezier ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto placeActionItem = MenuItemFont::create(" place ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto scaleActionItem = MenuItemFont::create(" scale ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto rotateActionItem = MenuItemFont::create(" rotate ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto showHideActionItem = MenuItemFont::create(" show/hide ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto blinkActionItem = MenuItemFont::create(" blink ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto fadeActionItem = MenuItemFont::create(" fade ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));
    auto tintActionItem = MenuItemFont::create(" tint ", CC_CALLBACK_1(HelloWorld::actionKindChange, this));

    auto actionKindMenu = Menu::create(moveActionItem, jumpActionItem, bezierActionItem, placeActionItem, scaleActionItem, rotateActionItem,
        showHideActionItem, blinkActionItem, fadeActionItem, tintActionItem, nullptr);
    actionKindMenu->setName("actionKindMenu");
    actionKindMenu->setPosition(actionKindMenuPos);
    actionKindMenu->alignItemsHorizontally();
    this->addChild(actionKindMenu);

    // action 실행 및 원상복귀 메뉴
    auto doItem = MenuItemFont::create(" do ", CC_CALLBACK_1(HelloWorld::doOrUndo, this));
    auto resetItem = MenuItemFont::create(" reset ", CC_CALLBACK_1(HelloWorld::doOrUndo, this));
    doItem->setTag(1);
    resetItem->setTag(2);

    auto doOrUndoMenu = Menu::create(doItem, resetItem, nullptr);
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

void HelloWorld::actionKindChange(Ref * pSender) {
    auto pMenuItem = (MenuItemFont*)pSender;
    auto pMenuItemLabel = (Label*)pMenuItem->getLabel();
    actionKind = pMenuItemLabel->getString();

    auto actionKindMenu = getChildByName<Menu*>("actionKindMenu");
    for (auto elem : actionKindMenu->getChildren()) {
        auto item = (MenuItemFont*)elem;
        item->setColor(Color3B::WHITE);
        auto tempstr = ((Label*)item->getLabel())->getString();
        if (actionKind == tempstr) item->setColor(Color3B::BLACK);
    }

    return;
}

void HelloWorld::doOrUndo(Ref* pSender) {
    allocateActions();
    auto item = (MenuItemFont*)pSender;

    if (item->getTag() == 2) {
        // reset
        pMan->removeFromParentAndCleanup(true);
        pGirl->removeFromParentAndCleanup(true);
        pMan = Sprite::create("Images/grossini.png");
        pGirl = Sprite::create("Images/grossinis_sister1.png");
        pMan->setPosition(pManInitPos);
        pGirl->setPosition(pGirlInitPos);
        this->addChild(pMan);
        this->addChild(pGirl);
        return;
    }

    // moveActionItem, jumpActionItem, bezierActionItem, placeActionItem, scaleActionItem, rotateActionItem,
    // showHideActionItem, blinkActionItem, fadeActionItem, tintActionItem
    if (actionKind == " move ") {
        pMan->runAction(myMoveTo);
        pGirl->runAction(myMoveBy);
        return;
    }
    if (actionKind == " jump ") {
        pMan->runAction(myJumpTo);
        pGirl->runAction(myJumpBy);
        return;
    }
    if (actionKind == " bezier ") {
        pMan->runAction(myBezierTo);
        pGirl->runAction(myBezierBy);
        return;
    }
    if (actionKind == " place ") {
        pMan->runAction(myPlace);
        log("Place action does not have by or to");
        return;
    }
    if (actionKind == " scale ") {
        pMan->runAction(myScaleTo);
        pGirl->runAction(myScaleBy);
        return;
    }
    if (actionKind == " rotate ") {
        pMan->runAction(myRotateTo);
        pGirl->runAction(myRotateBy);
        return;
    }
    if (actionKind == " show/hide ") {
        pMan->runAction(myShow);
        pMan->runAction(myHide);
        return;
    }
    if (actionKind == " blink ") {
        pMan->runAction(myBlink);
        log("Blink action does not have by or to");
        return;
    }
    if (actionKind == " fade ") {
        pMan->runAction(myFadeOut);
        //pGirl->runAction(myFadeOut);
        return;
    }
    if (actionKind == " tint ") {
        pMan->runAction(myTintTo);
        pGirl->runAction(myTintBy);
        return;
    }
}

void HelloWorld::allocateActions() {
    myMoveTo = MoveTo::create(2, Vec2(400, 0));
    myMoveBy = MoveBy::create(2, Vec2(400, 0));

    myJumpTo = JumpTo::create(2, Vec2(400, 0), 50, 3);
    myJumpBy = JumpBy::create(2, Vec2(400, 0), 50, 3);

    ccBezierConfig bzConf;
    bzConf.controlPoint_1 = Vec2(150, 150);
    bzConf.controlPoint_2 = Vec2(300, -150);
    bzConf.endPosition = Vec2(400, 0);
    myBezierTo = BezierTo::create(2, bzConf);
    myBezierBy = BezierBy::create(2, bzConf);

    myPlace = Place::create(Vec2(400, 160));

    myScaleTo = ScaleTo::create(2, 1.2f);
    myScaleBy = ScaleBy::create(2, 1.2f);

    myRotateTo = RotateTo::create(2, -90);
    myRotateBy = RotateBy::create(2, -90);

    myShow = Show::create();
    myHide = Hide::create();

    myBlink = Blink::create(2, 6);

    myFadeOut = FadeOut::create(2);
    myFadeIn = FadeIn::create(1);

    myTintTo = TintTo::create(2, Color3B::BLACK);
    myTintBy = TintBy::create(2, -50, -50, -50);
}