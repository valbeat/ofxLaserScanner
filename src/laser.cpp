//
//  laser.cpp
//  LaserScanner
//
//

#include "laser.h"
Laser::Laser(LightColor _color, int _brightness) {
    color = _color;
    brightness = _brightness;
}

bool Laser::isHit(ofColor c) {
    // スクリーンの明るさが設定した明るさより明るければ当たっていると判断
    if(getScreenBrightness(c) > brightness) {
        return true;
    }
    return false;
}

void Laser::setBrightness(int _brightness) {
    brightness = _brightness;
}

int Laser::getScreenBrightness(ofColor c) {
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

