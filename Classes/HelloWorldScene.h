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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    HelloWorld();

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::Sprite* pMan;
    cocos2d::Sprite* pGirl;

    cocos2d::Vec2 actionKindMenuPos;
    cocos2d::Vec2 actionDoMenuPos;
    cocos2d::Vec2 pManInitPos;
    cocos2d::Vec2 pGirlInitPos;
    std::string actionKind;

    void actionKindChange(Ref* pSender);
    void doOrUndo(Ref* pSender);

    // moveActionItem, jumpActionItem, bezierActionItem, placeActionItem, scaleActionItem, rotateActionItem,
    // showHideActionItem, blinkActionItem, fadeActionItem, tintActionItem
    cocos2d::MoveTo* myMoveTo;
    cocos2d::MoveBy* myMoveBy;

    cocos2d::JumpTo* myJumpTo;
    cocos2d::JumpBy* myJumpBy;

    cocos2d::BezierTo* myBezierTo;
    cocos2d::BezierBy* myBezierBy;

    cocos2d::Place* myPlace;

    cocos2d::ScaleTo* myScaleTo;
    cocos2d::ScaleBy* myScaleBy;

    cocos2d::RotateTo* myRotateTo;
    cocos2d::RotateBy* myRotateBy;

    cocos2d::Show* myShow;
    cocos2d::Hide* myHide;

    cocos2d::Blink* myBlink;

    cocos2d::FadeOut* myFadeOut;
    cocos2d::FadeIn* myFadeIn;

    cocos2d::TintTo* myTintTo;
    cocos2d::TintBy* myTintBy;

    cocos2d::Color3B originColorMan;
    cocos2d::Color3B originColorGirl;

    void allocateActions();
};

#endif // __HELLOWORLD_SCENE_H__
