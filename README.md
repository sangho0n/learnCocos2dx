![image](https://user-images.githubusercontent.com/54069713/226094028-5e77d041-760d-4d1e-a066-5d0d24bc5d10.png)

# 0. learnCocos2dx

코코스2dx 엔진을 배워봅시다 (v 4.0)


- 이 레포지토리는 [핵심강좌! Cocos2d-x] 도서를 보면서 알게된 내용을 정리한 저장소입니다.

- 모든 공부 내용들은 이곳 master 브랜치의 readme에 정리되며, 자세한 코드는 해당 브랜치로 이동하여 볼 수 있습니다.

- 브랜치명은 도서의 각 절의 번호와 이름을 참고하여 지었습니다.

--------
# 1. 입문
## Cocos2d-x란?
![image](https://user-images.githubusercontent.com/54069713/226093958-110a968f-bdc9-4ff7-a857-4fc764c3a074.png)

- Coocs2d : OpenGL을 기반으로 한 게임엔진. 파이썬으로 구현되어 있다.
- Cocos2d-iPhone

아이폰 등장 이후 아이폰을 지원하기 위해 Objective-C언어로 다시 작성된 버전
- Cocos2d-X

중국의 개발자 왕저에 의해 C++로 포팅된 버전. 개발과 배포 모두 플랫폼에 종속적이지 않게 되었다.

## why cocos2d-x?

크로스플랫폼을 지원하는 2D 게임엔진이기 때분에 별도의 코드수정 없이 바로 iOS/Android 앱을 만들 수 있다. 개발도 맥, 윈도우, 리눅스 환경을 모두 지원한다. (다만, 아이폰이나 아이패드의 경우 최종 컴파일이 맥에서 이루어져야 하기 때문에, 다른 플랫폼에서 개발이 가능하긴 하나 최종적으로는 맥에서 컴파일하는 과정이 필요함)

오픈소스임과 동시에 무료이다. 2d 게임의 개발을 목적으로 한 엔진이기 때문에 유니티에 비해 용량이 적고 속도가 빠르다. 국내에서도 꽤 많은 모바일 게임사들이 코코스2d-x를 채택하고 있다.

~~에디터 기반 엔진인 코코스 크리에이터가 등장하고, 추콩사(코코스 개발사)가 Cocos2d-X 4.0 이후로 개발을 중단한다고 발표한 후로 레거시로 남을 것 같긴 하다만, 2d-x 역시 웰메이드 엔진이라 빠르게 전환될 것 같지는 않을 것이라고 믿는다 ㅎㅎ~~

## 개발환경 구축(window 기준)
### 과정
- visual studio community 설치
- python 설치
- CMake 설치
- cocos2d-x 설치
- 프로젝트 생성

도서가 3.x 버전을 기준으로 기술되어 있기에, [블로그](https://bakcoding.github.io/cocos/cocos001-test/)를 참고하여 작성하였습니다.

### Visual Studio Community 설치
버전을 잘 기억해두자! 프로젝트 생성 시 사용된다.

작성자의 경우 Microsoft Visual Studio Community 2019 Version 16.11.18로 설치함

(이미 설치했다면, Help > About Microsoft Visual Studio를 통해 확인 가능)

### Python 설치
3버전이 아닌 2버전 설치 필요. 설치 이후 환경변수 설정을 해줘야한다.
### CMake 설치
cmake는 makefile(빌드 스크립트)를 만들어주는 툴이다. 3.1버전 이상 설치 필요.
### Cocos2d-X 
Cocos2d-X 4.0 버전 다운로드.

```
cd (설치된 경로)
python setup.py
```
### 프로젝트 생성
- 프로젝트 생성
```
cd (프로젝트를 생성할 경로)
cocos new (프로젝트명) -p (패키지명) -l cpp
```
- 솔루션 생성
```
cd (프로젝트 루트 경로)
md win32-build  --win32-build 폴더 생성
cd win32-build  --win32-build 폴더로 이동
cmake .. -G"(설치된 비주얼스튜디오 버전; ex. Visual Studio 16 2019)" -A win32
```
이후 비주얼 스튜디오 에디터로 들어가 생성한 프로젝트를 시작 프로젝트로 설정해준 후 실행시켜보자.

아래 화면이 나온다면 성공

![image](https://user-images.githubusercontent.com/54069713/226095725-77a6654d-3db1-4653-94b9-476f9f5e711c.png)

--------
# 2. 기초
Cocos2d-x는 노드를 기준으로 디렉터, 씬, 레이어, 스프라이트의 계층적인 포함관계를 맺고,

액션 클래스를 통해 애니메이션을 구현한다.

## 기본 구성 요소
- 노드

최상위 클래스. 위치, 색상, 카메라 등의 여러 프로퍼티가 있음. 자체적으로 스케줄러를 포함하고 있음.
- 디렉터

싱글톤 클래스. 씬들을 관리하는 기능을 수행.
- 씬과 레이어

씬과 레이어는 스프라이트, 레이블, 메뉴 등과 같은 클래스들을 자식으로 가질 수 있음.
3.0 버전 이전의 씬 객체는 레이어와 달리 터치이벤트를 처리하지 못하였으나, 이후로는 씬도 터치이벤트를 받을 수 있게됨.
따라서 3.0 버전 이후의 레이어는 주로 터치이벤트를 처리하는 데 사용되기보다는 여러 객체들을 그룹화하는데 주로 사용된다.

하나의 씬에는 여러 레이어들이 포함될 수 있다. 예를들어 일반적인 게임의 시작 씬의 경우 메뉴(or HUD) 레이어, 배경 레이어, 캐릭터 레이어 등으로 구성될 수 있다.

- 스프라이트

이미지 파일을 화면에 출력하는 역할을 수행. 파일 로딩과 화면 출력과 관련된 여러 메서드들이 정의되어 있다.
- 액션

스프라이트의 애니메이션 및 동적 처리를 위한 클래스. 이동, 회전, 점프, 크기변환 등
- etc

Sound, Particle, Box2d, Chipmonk 등...

## 좌표계
- UI 좌표계 (iOS, Android 화면 기준)

![image](https://user-images.githubusercontent.com/54069713/226122125-35275a7b-684b-4096-9b2c-0a023bcf5020.png)

- OpenGL 및 Cocos2d-X 좌표계

![image](https://user-images.githubusercontent.com/54069713/226122205-fb00f694-c716-45fc-9828-bfef356b44c1.png)

## 앵커포인트

화면배치 및 회전의 기준. (0, 0) ~ (1, 1)로 나타나며, default는 (0.5, 0.5)
## 자료형
- cocos2d::Vec2 : 2차원 벡터
- cocos2d::Size : 2차원 크기. width와 height를 갖는다.
- cocos2d::Rect : 2차원 직사각형. 좌측 하단의 좌표(Vec2)와 그려질 크기인 Size를 담고 있다.
- cocos2d::Color3B : RGB
- cocos2d::Color4B : RGBA
- cocos2d::Vector : std::vector의 확장판. 메모리 관리를 자동으로 해준다.

--------
# 3. 스프라이트
## 스프라이트 불러오기 및 앵커포인트 예시
- Sprite::create로 이미지 로딩
- 위치, 앵커포인트 설정
- 씬의 child로 등록

![image](https://user-images.githubusercontent.com/54069713/226123104-f6e26d20-551a-43f7-b7af-312b12e2888b.png)

위치는 화면 중앙, 앵커포인트는 0, 0으로 설정된 모습
## Z-Order 예시
- 씬의 child로 등록할 때 지정 가능
```cpp
this->addChild(sprite, 2);
```
- 씬에 등록한 후 동적으로 지정 가능
```cpp
sprite->setLocalZOrder(2);
```
![image](https://user-images.githubusercontent.com/54069713/226123161-374255d6-c489-4ed4-b547-5cf053a99543.png)

## 프로퍼티 예시

흰색 네모 모양의 스프라이트를...

- 일부분만 잘라와 사용
```cpp
    pRect->setTextureRect(Rect(0, 0, 150, 150));
    pRect->setPosition(Vec2(240, 160));
```
- 색 지정
```cpp
    pRect->setColor(Color3B(0, 0, 255)); // blue
```
- 크기 변환, 회전, 투명도(0 ~ 255) 프로퍼티 설정
```cpp
    pRect->setScale(1.5f);
    pRect->setRotation(45.0f);
    pRect->setOpacity(160);
```
![image](https://user-images.githubusercontent.com/54069713/226124422-0af12efb-03a0-4713-8404-1c0cbab18848.png)

## 부모 스프라이트와 자식 스프라이트
자식 스프라이트는 부모 스프라이트를 기준으로 좌표계를 갖는다.

예시이미지 : 빨간색 막대기 스프라이트를 사람 스프라이트의 자식으로 등록한 모습

![image](https://user-images.githubusercontent.com/54069713/226373575-225ad8e9-877e-4dda-9022-2a9177912152.png)

-------
# 4. 레이블
## 시스템 폰트
4.0부터 Lable::create(text, sysfont, fontSize, ..) 메서드가 사라지면서 시스템폰트를 사용하려면 create() 메서드로 생성 후 하나씩 지정해주거나, createWithSystemFont()메서드를 직접 호출해야함.

글씨체나 폰트사이즈, 글자색뿐만 아니라 글씨가 서지는 구역의 사이즈, 정렬 옵션을 지정해줄 수 있다.

![image](https://user-images.githubusercontent.com/54069713/226389809-861119cd-c518-48fd-a6a2-5d6d9bf6ad1f.png)

## 비트맵 폰트
비트맵폰트는 이미지 파일 기반의 폰트이다. 글자 하나마다 별개의 스프라이트로 관리하므로 한 글자마자 다른 효과를 부여할 수 있다.

비트맵폰트를 사용하려면 동일한 이름의 fnt 파일과 png 파일이 필요하다.

![image](https://user-images.githubusercontent.com/54069713/226917938-77130a53-f85e-4a8c-adf1-dbbb01ac07bd.png)

## 캐릭터맵
캐릭터맵은 비트맵과 동일한 특성을 지닌다. 그러나 비트맵과는 달리 png 파일 하나만으로 레이블을 생성해낼 수 있다.

생성 시 높이, 너비, 시작 아스키코드 문자를 지정해줘야 하는데, plist xml 파일을 사용할 경우 이 부분 역시 코드 밖으로 빼낼 수 있다.

![image](https://user-images.githubusercontent.com/54069713/226922842-9127faa2-cc68-4c8c-a72e-f102354dd82e.png)

## 트루타입 폰트
ttf 파일을 임포트하여 사용하는 방식. 시스템폰트와 달리 플랫폼에 종속적이지 않다.

![image](https://user-images.githubusercontent.com/54069713/226931848-397dd3ca-543f-4086-bd9f-65a477ba58d3.png)


-------
# 5. 메뉴
## 메뉴와 메뉴아이템
Menu::create 메서드를 사용하면 빈 메뉴를 생성할 수 있다. 이렇게 생성된 인스턴스에는 메뉴아이템을 추가할 수 있다. 4.0버전에서 지원하는 메뉴아이템은 다음과 같다.
- MenuItem
- MenuItemAtlasFont
- MenuItemFont
- MenuItemImage
- MenuItemLabel
- MenuItemSprite
- MenuItemToggle

프로그래머가 직접 메뉴와 메뉴아이템의 위치를 지정해줄 수도 있고, 지정된 메서드를 사용해 위치와 정렬 방식을 지정할 수도 있다.

## 메뉴아이템이미지
이미지를 메뉴아이템으로 사용할 수 있다. MenuItemImage::create 메서드로 인스턴스 생성 시 평상시 이미지, 선택시 이미지, 비활성화시 이미지, 콜백함수를 지정해줄 수 있다.

추가한 세 버튼 중 가운데 버튼을 클릭한 모습

![image](https://user-images.githubusercontent.com/54069713/227931328-0b9c2be5-6d3e-40fc-82dc-e24dd08d7bc7.png)

## 위치 지정
메뉴와 메뉴아이템의 위치를 프로그래머가 임의로 지정해줄 수 있다.

우측 상단에 있는 전원버튼을 눌렀을 때 콜백함수 내의 로그가 찍히는 모습

![image](https://user-images.githubusercontent.com/54069713/227931776-2c7014da-82fa-4635-b1e4-fd2e258bcb6b.png)

## 메뉴아이템폰트
MenuItemFont 인스턴스를 사용하면 프로그래머가 원하는 텍스트를 바로 메뉴아이템으로 만들 수 있다.
MenuItemFont::create 메서드는 인자로 text와 콜백함수(optional)를 받는다.

왼쪽부터 오른쪽으로 태깅하여 콜백함수를 통해 로그를 찍어본 모습. 1번 버튼과 2번 버튼은 메뉴아이템폰트 인스턴스이다.

![image](https://user-images.githubusercontent.com/54069713/228145697-d038b684-9167-4f98-ba5c-d4166925d542.png)

## 태그 사용하기
메뉴아이템 말고도 cocos2d-x의 모든 노드에는 태그를 설정해줄 수 있다.

한편 메뉴아이템에 등록된 콜백함수는 Ref* 타입의 인자를 받는다. Ref 클래스는 레퍼런스 카운팅을 위해 사용되는 클래스로, Cocos2d-x의 Node 클래스는 Ref 클래스를 상속받는다. [출처](https://docs.cocos2d-x.org/api-ref/cplusplus/V3.15/df/d28/classcocos2d_1_1_ref.html)

브랜치 5.5-menu-tag-sprite에서는 같은 콜백함수 내에서 sender의 태그를 확인해 각각 다른 기능을 수행하도록 구현하였다. generate 메뉴아이템을 누르면 스프라이트가 생성되고, remove 버튼을 누르면 스프라이트가 삭제된다. 스프라이트에 태깅을 하여 원하는 스프라이트를 바로 얻어와 삭제할 수 있도록 구현한 모습이다.

generate 메뉴아이템 클릭 시

![image](https://user-images.githubusercontent.com/54069713/228149450-783bda94-cd7d-43b4-acd5-74d8e7ca1191.png)

remove 메뉴아이템 클릭 시

![image](https://user-images.githubusercontent.com/54069713/228149546-6166c286-35c7-473a-b99d-7b00b0774bd0.png)

-------
# 6. 액션
## 액션이란?
Action은 말 그대로 이동, 회전, 크기변환 등 스프라이트 및 노드들을 변환하는  기능을 제공하는 클래스이다. 교재에서는 다음과 같은 기준으로 액션을 나누고 있다.

|종류|설명|
|------|---|
|Basic Action|기본으로 제공되는 singular 액션(Move, Jump, Rotate, Scale, Tint, Bezier, Place, Blink, Show/Hide(+ ToggleVisibiltiy), Fade)|
|Composition Action|복합 액션|
|Ease Action|진행속도를 조절할 수 있는 액션|
|CallFunc Action|콜백 액션|

한편, [공식문서](https://docs.cocos2d-x.org/cocos2d-x/v4/en/actions/getting_started.html)는 다음과 같은 기준으로 나누고 있다.


|종류|설명|
|------|---|
|Basic Action|기본으로 제공되는 singular 액션(위 분류에서 ease action이 이곳에 포함됨)|
|Sequences|복합 액션|

그리고 CallFunc는 Sequence::create() 메서드의 인자로 들어갈 수 있는 오브젝트라고 설명하고 있다.
본 레포지토리에서는 전자의 순서를 기준으로 액션을 설명하겠지만, 원칙은 공식문서를 따름에 유의하자.

한편 move와 jump 등의 액션들은 by 액션과 to 액션으로 나눌 수 있다.
- By : 현재 위치 + Vec2를 한 곳으로 이동 or 현재 색상 + (deltaR, deltaG, deltaB)으로 색 변환
- To : 현재 위치에서 Vec2로 주어진 곳까지 이동 or 주어진 Color3B(또는 rgb)까지 이동

따라서 동일한 Vec2(및 Color)를 기준으로 By 액션을 여러번 적용하면 적용한 만큼 변환되지만, To 액션은 한번만 변환된다. 

## 기본 액션 Basic Action
교재에서는 다음과 같이 기본 액션들을 분류하고 있다.(앞서 말했듯, Ease action은 이 설명에는 포함되지 않음)
|기능 분류|액션 종류|
|------|---|
|위치 변경|MoveBy, MoveTo, JumpBy, JumpTo, BezierBy, BezierTo, Place|
|크기 변경|ScaleBy, ScaleTo|
|회전 변경|RotateBy, RotateTo|
|가시성 변경|Show, Hide, Blink, ToggleVisibility|
|투명도 변경|FadeIn, FadeOut, FadeTo|
|색상 변경|TintBy, TintTo|

### Move
- By : 주어진 시간 동안, 현재위치 + 주어진 Vec2까지 이동
- To : 주어진 시간 동안, 주어진 Vec2까지 이동
### Jump
- By : MoveBy + 이동하면서 주어진 높이를 주어진 횟수만큼 점프 
- To : MoveTo + 이동하면서 주어진 높이를 주어진 횟수만큼 점프
### Bezier
- By : MoveBy + 베지어 곡선을 그리며 이동
- To : MoveTo + 베지어 곡선을 그리며 이동

한편 베지어 곡선의 정보는 ccBezierConfig를 통해 전달되며, 컨트롤 포인트 1, 컨트롤 포인트 2, 목표 지점의 좌푯값이 해당 인스턴스에 포함된다.
### Place
주어진 곳으로 순간이동
### Scale
- By : 주어진 시간 동안, 현재 크기 * 주어진 스케일 값으로 변화
- To : 주어진 시간 동안, 원래 크기 * 주어진 스케일 값으로 변화
### Rotate
- By : 주어진 시간 동안, 시계방향으로 주어진 각도만큼 회전
- To : 주어진 시간 동안, 주어진 각도로 회전(가장 짧은 방향)

한편 각도는 육십분법으로 넘겨주어야 한다. 한가지 의문인 것은, 오픈지엘 좌표계를 따름에도 불구하고 왜 회전에서의 양의 방향이 시계방향인지는 좀 의문이다.. 이유를 알게 되면 추가하겠다. ~친절한 챗지피티 왈 : 코코스가 오픈지엘을 사용하는 것은 맞지만, 시계방향을 회전에 있어 양의 방향으로 설정하는 것이 일반인에게 있어 좀 더 이해하기 쉬워서 그렇게 한 것이 아닐까...~

-90 방향으로 1번 및 2번 회전시킨 경우(남자는 To, 여자는 By; 여자가 반시계방향으로 돌아감)

![image](https://user-images.githubusercontent.com/54069713/228423797-8c19717f-4786-49de-a914-30463c18fbe7.png)
![image](https://user-images.githubusercontent.com/54069713/228423859-43863c3d-cf84-48e4-866e-d209681a5893.png)


270 방향으로 1번 및 2번 회전시킨 경우(여자가 시계방향으로 돌아감)

![image](https://user-images.githubusercontent.com/54069713/228423639-4ef13950-2e0e-4f8f-b756-b620d6cf3ef3.png)
![image](https://user-images.githubusercontent.com/54069713/228423919-0ad213ce-9ab1-4385-b4fc-cd706a08ed9a.png)
### Show/Hide
보여주거나 숨김
### Blink
주어진 시간 동안 주어진 횟수 만큼 깜빡임
### ToggleVisibility
현재의 가시성 여부를 뒤집음
### Fade
- In : 주어진 시간 동안 점점 나타남
- Out : 주어진 시간 동안 점점 사라짐
- To : 주어진 시간 동안 주어진 투명도로 변화함
### Tint
- By : 주어진 시간 동안 현재 색상 + (deltaR, deltaG, deltaB)로 변화
- To : 주어진 시간 동안 주어진 Color3B(혹은 r, g, b)로 변화

## 복합 액션
### Sequence
주어진 순서대로(배열로 주어진 경우 0번 인덱스부터 순차적으로) 액션 실행. DelayTime*를 인자로 넣어주면 시간 지연도 가능함.
### Spawn
동시에 모든 액션 실행.
### Repeat
- Repeat::create(FinitTimeAction*, uint)

주어진 액션을 주어진 횟수만큼 반복

- RepeatForever::create(ActionInterval*)

주어진 액션을 무한정 반복

스폰, 시퀀스, 리피트 등을 적절히 이용하여 애니메이션을 구현한 모습


![복합액션](https://user-images.githubusercontent.com/54069713/229723759-c572a9b8-3b9d-4c54-a12e-3ed0c9912837.gif)

## 이즈 액션
재생속도를 조절할 수 있는 액션. Ease 접두사가 붙은 것 말고도 Speed로도 액션의 속도를 조절할 수 있다. 이즈액션은 마치 물리엔진이 적용되있는 것처럼 스프라이트를 움직이고싶을 때 사용할 수 있다. [출처](https://docs.cocos2d-x.org/cocos2d-x/v4/en/actions/basic.html)

접미사 In, Out, InOut에 따라 속도가 변하는 형태가 다르다.
- In : 천천히->빨라짐
- Out : 빠름->느려짐
- InOut : 느림->빨라짐->느려짐

![image](https://user-images.githubusercontent.com/54069713/229844138-043c4ceb-f65d-4672-8b4c-c02ca2250b0f.png)

여러 이즈 액션들을 사용하는 모습. 맨 위부터 차례대로 MoveBy, ~In, ~Out, ~InOut 액션에 해당한다.
(단, Speed의 경우 1배, 2배, 3배, 4배)

![이즈액션](https://user-images.githubusercontent.com/54069713/229841492-843395a3-ce1b-4686-9641-2c266f55d4ce.gif)

위 gif에서 일반적인 EaseIn과 EaseOut, EaseInOut은 반대로 움직이는데, 그 이유는 이번 예제에서는 rate을 0.4f로 주었기 때문이다. rate을 1이 넘는 값을 준다면 의도한 대로 동작한다.

일반적인 Ease, EaseElastic, EaseBounce, EaseBack 말고도 EaseExponential, EaseSine, EaseQuadratic, EaseQuartic, EaseQuintic, EaseCircle, EaseCubic 등의 액션들이 존재한다. 각각에 대한 자세한 설명은 [공식문서](https://docs.cocos2d-x.org/api-ref/cplusplus/V4.0/db/dcf/classcocos2d_1_1_action_ease.html)를 참고할 것.

## CallFunc
CallFunc 인스턴스를 이용하면 복합 액션에 사용자가 원하는 메서드를 등록할 수 있다.

브랜치 6.3 예시에서 Sequnce 액션에 원하는 CallFunc 인스턴스(이 예시에서는 Sender를 원래 위치로 돌려놓는다)를 단 모습.

![CallFunc](https://user-images.githubusercontent.com/54069713/230562934-597049c1-a224-4c4c-97ca-7dc83c025eda.gif)

Sequence를 사용한 액션인 moveAndScaleUp과 rotAfter2s 메뉴아이템을 눌렀을 때는 reset 메뉴아이템을 누르지 않아도 원래 위치로 돌아가지만, rotTwice 메뉴아이템은 Sequence가 아닌 Repeat을 사용한 액션이기 때문에 자동으로 원래 위치로 돌아가지 않는다.

-------
# 7. 애니메이션
## Animation과 Animate
- Animation : 어떤 애니메이션이 재생되는지 명세하는 클래스. 프레임단위로 지정할 수 있으며, 프레임 사이 시간도 조정할 수 있다.
- Animate : 지정된 애니메이션의 재생 정보를 담는 클래스.

애니메이션의 프레임은 하나씩 지정할 수도 있고, 아틀라스(스프라이트 시트)로 묶인 파일로 지정할 수도 있으며, plist파일로 불러올 수도 있다.

아틀라스로 프레임들을 지정할 때는 1. Sprite::getTexture() 메서드를 통해 텍스쳐를 부르거나, 2. 텍스쳐캐시에 이미지를 등록한 후 사용하여야 한다. 이후 Animation::addSpriteFrameWithTexture 메서드를 이용하여 프레임들을 지정할 수 있다.

plist파일을 이용할 때는 스프라이트 프레임 캐시에 plist 파일을 등록한 후(spriteFrameCache->addSpriteFramesWithFile 메서드), plist파일에 등록되어 있는 이름을 이용하여 애니메이션 프레임들을 지정할 수 있다.

아틀라스와 plist 파일을 이용한 애니메이션들의 구동 모습

![Animation](https://user-images.githubusercontent.com/54069713/232326541-ad31470e-d219-45f5-9a0f-8130457c9006.gif)

-------
# 8. 스프라이트 캐시
-------
# 스케줄
-------
# 프로그레스 타이머
-------
# 터치
-------
# 충돌처리
-------
# 큰 배경
-------
# 사운드
-------
# 씬 트랜지션
-------
# 파티클 시스템
-------
# 데이터 저장
-------
# 사용자 입력
-------ptjem
# 스크롤
-------
# 테이블
-------
# 리소스 데이터
-------
# HTTP 통신
-------
# 타일맵
-------
# Box2D 물리엔진
