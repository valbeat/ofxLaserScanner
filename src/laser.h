//
//  laser.h
//  LaserScanner
//
//  Created by kajikawa on 1/27/16.
//
//

#ifndef laser_h
#define laser_h

#define COLOR Green   // レーザーの色
#define BRIGHT 250  // レーザーの明るさ

#include "ofMain.h"

class Laser {
public:
    enum LightColor{ Red, Green, Blue}; // 色の定義
    bool isHit(ofColor c); // 光量からレーザーが当たっているかどうかを判断する
    void setBright(int bright); // 明るさを設定する
    
    Laser(LightColor _color = COLOR, int _bright = BRIGHT);
    
private:
    LightColor color;   // レーザーの色 (赤，緑，青)
    int bright;     //レーザーの明るさ (0 ~ 255)
    int getScreenBright(ofColor c); // スクリーン上に写った時の明るさを取得
};


#endif /* laser_h */
