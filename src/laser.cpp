//
//  laser.cpp
//  LaserScanner
//
//  Created by kajikawa on 1/27/16.
//
//

#include "laser.h"
Laser::Laser(EColor _color, int _bright) {
    color = _color;
    bright = _bright;
}

bool Laser::isHit(ofColor c) {
    // スクリーンの明るさが設定した明るさより明るければ当たっていると判断
    if(getScreenBright(c) > bright) {
        return true;
    }
    return false;
}

int Laser::getScreenBright(ofColor c) {
    // レーザーの色によって必要な色の明るさを取得
    switch (color) {
        case Red:
            return c.r;
        case Green:
            return c.g;
        case Blue:
            return c.b;
        default:
            return 0;
    }
}