//
//  laser.h
//  LaserScanner
//
//  Created by kajikawa on 1/27/16.
//
//

#ifndef laser_h
#define laser_h

#define COLOR Red   // レーザーの色
#define BRIGHT 250  // レーザーの明るさ

#include "ofMain.h"

class Laser {
public:
    enum EColor{ Red, Green, Blue}; // 色の定義
    
    bool isHit(ofColor c); // 光量からレーザーが当たっているかどうかを判断する
    
    Laser(EColor _color = COLOR, int _bright = BRIGHT);
    
private:
    EColor color;   // レーザーの色 (赤，緑，青)
    int bright;     //レーザーの明るさ (0 ~ 255)
    int getScreenBright(ofColor c); // スクリーン上に写った時の明るさを取得
};


#endif /* laser_h */
