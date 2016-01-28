//
//  laserScanner.cpp
//  LaserScanner
//
//  Created by kajikawa on 2016/01/20.
//
//

#include "laserScanner.h"

//--------------------------------------------------------------
void LaserScanner::setup(int w, int h) {
    
    width = w;
    height = h;
    
    laserScan.allocate(width, height, GL_RGB);
    laserScan.begin();
    ofClear(0,255);
    laserScan.end();

    setupPointCloud();
    
    laser = *new Laser();

}
void LaserScanner::setupPointCloud() {
    pointCloud.clearVertices();
    pointCloud.setMode(OF_PRIMITIVE_POINTS);
}

void LaserScanner::start() {
    isStart = true;
}
void LaserScanner::update() {
    if (isStart) {
        updateRotate();
    }
    ofPixels pixels;
    image.readToPixels(pixels);
    readLaserPixels(pixels);
//
//    calc();
}

void LaserScanner::setImage(ofFbo source){
    image = source;
}

ofFbo LaserScanner::getImage(){
    return laserScan;
}

//--------------------------------------------------------------
// 計算部分
void LaserScanner::calc() {
    int Nx = image.getWidth(); // スクリーン幅のpixel数
    int Ny = image.getHeight(); // スクリーン高さのpixel数
    float Lw; // スクリーンの大きさ[mm]
    int lookPoint = (int)(Nx / 2); // 注視点（カメラの中心）
    
    // レーザーの基準値 dの[mm]→[pixel]変換
    x0 = (int)(d * RESOLUSION_WIDTH / 25.4); // [pixel]
    Lw = Nx / RESOLUSION_WIDTH * 25.4; // [mm]
    for (int i = 0; i < laserPos.size(); i++) {
        ofPoint pos = laserPos[i];
        float diff = abs(pos.x - lookPoint) - x0;
        if(diff < 0) diff = 0;
        ofPoint p;
        float rad = rotate * DEG_TO_RAD;
        p.y = (-pos.y + Ny / 2) / RESOLUSION_HEIGHT * 25.4;
        p.z = - Lz * cos(rad) * (1 - Nx * d / (Nx * d + Lw * diff));
        p.x = Lz * sin(rad) * (1 - Nx * d / (Nx * d + Lw * diff));
        pts.push_back(p);
    }
}
//--------------------------------------------------------------
void LaserScanner::readLaserPixels(ofPixels pixels) {
    // レーザースキャン結果のリセット
    laserScan.begin();
    ofClear(0,255);
    laserScan.end();

    // ピクセル数の取得
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    
    
    for (int y = 0; y < h; y+= laserPointInterval) {
        vector<int> v;
        for (int x = 0; x < w ; x++) {
            
            ofColor c = pixels.getColor(x, y);
            
            // 緑成分の閾値で判定
            if(laser.isHit(c)) {
                v.push_back(x);
            }
        }
        
        if (!v.empty()) {
            int mX = Utility::median(v);
            laserPos.push_back(ofPoint(mX,y));
            
            // レーザーの中心を表示させる
            laserScan.begin();
            // ブレンドモードをONにした時はスムージングを切る
            ofDisableSmoothing();
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(0,255,0);
            ofRect(mX - 1, y, 2, 2);
            ofSetColor(255, 255, 255);
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            laserScan.end();
        }
    }
}
//--------------------------------------------------------------
void LaserScanner::updateRotate() {
    int r = rotate;
    if (r >= 360) {
        isStart = false;
        return;
    }
    r += rotateInterval;
    if (r > 359) r = 359;
    rotate = r;
}
//--------------------------------------------------------------
// ポイントクラウド生成
void LaserScanner::createPointCloud() {
    if (pts.empty()) {
        return;
    }
    pointCloud.clear();
    for (int i = 0; i < pts.size(); i++) {
        ofPoint pos = pts[i];
        pointCloud.addVertex(pos);
    }
}

