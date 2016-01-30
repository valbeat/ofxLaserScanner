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
    drawLaserPoints(laserPos);
    calc();
    
    laserPos.clear();
}
void LaserScanner::setLaserBrightness(int brightness) {
    laser.setBrightness(brightness);
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
    int lookPoint = (int)(Nx / 2); // 注視点（カメラの中心）
    float Lw = Nx / RESOLUSION_WIDTH * 25.4; // スクリーン幅[pixel]→[mm]
    x0 = (int)(d * RESOLUSION_WIDTH / 25.4); // レーザーの基準値[mm]→[pixel]
    for (ofVec2f pos : laserPos) {
        float diff = abs(pos.x - lookPoint) - x0; // カメラの中心とのレーザーの位置の差分を取る
        if(diff < 0) diff = 0; // 差分がない場所はモデルが無い場所とみなす
        ofVec3f pos3d;
        float rad = rotate * DEG_TO_RAD; // 角度をradianに変換
        pos3d.y = (-pos.y + Ny / 2) / RESOLUSION_HEIGHT * 25.4;
        pos3d.z = - Lz * cos(rad) * (1 - Nx * d / (Nx * d + Lw * diff));
        pos3d.x = Lz * sin(rad) * (1 - Nx * d / (Nx * d + Lw * diff));
        pts.push_back(pos3d);
    }
}
//--------------------------------------------------------------
void LaserScanner::readLaserPixels(ofPixels pixels) {

    // ピクセル数の取得
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    
    // レーザーの位置を取得
    for (int y = 0; y < h; y+= laserPointInterval) {
        vector<int> vX; // xを格納
        for (int x = 0; x < w ; x++) {
            ofColor c = pixels.getColor(x, y);
            
            // レーザーが当たっている場所であればvectorに追加
            if(laser.isHit(c)) {
                vX.push_back(x);
            }
        }
        
        if (!vX.empty()) {
            int mX = Utility::median(vX); // x座標の中央値を取得
            laserPos.push_back(ofVec2f(mX,y));
        }
    }
}
void LaserScanner::drawLaserPoints(vector<ofVec2f> vPosition) {
    // レーザーの中心を表示させる
    laserScan.begin();
    ofClear(0,255);
    ofDisableSmoothing(); // ブレンドモードをONにした時はスムージングを切る
    ofEnableBlendMode(OF_BLENDMODE_ADD); // 加算合成
    ofSetColor(0,255,0);
    for (ofVec2f p : vPosition) {
        ofRect(p.x - 1, p.y, 2, 2);
    }
    ofSetColor(255, 255, 255);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    laserScan.end();
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

