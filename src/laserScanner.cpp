//
//  laserScanner.cpp
//  LaserScanner
//
//  Created by kajikawa on 2016/01/20.
//
//

#include "laserScanner.h"

//--------------------------------------------------------------
void LaserScanner::setupCamera() {
    camWidth = 640;
    camHeight = 480;
    camera.setDesiredFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
    camera.setVerbose(true);
    camera.listDevices();
    camera.setDeviceID(1);
    camera.initGrabber(camWidth,camHeight);
}
//--------------------------------------------------------------
void LaserScanner::setupVideo(string videoName) {
    camWidth = 640;
    camHeight = 480;
    video.loadMovie(videoName);
    video.play();
}
//--------------------------------------------------------------
// 計算部分
void LaserScanner::calc() {
    int Nx = camWidth; // スクリーン幅[pixel]
    int Ny = camHeight;
    float Lw; // スクリーンの大きさ[mm]
    int lookPoint = (int)(camWidth / 2); // 注視点（カメラの中心）
    
    // レーザーの基準値 dの[mm]→[pixel]変換
    x0 = (int)(d * RESOLUSION_WIDTH / 25.4); // [pixel]
    Lw = Nx / RESOLUSION_WIDTH * 25.4; // [mm]
    for (int i = 0; i < laserPos.size(); i++) {
        ofPoint pos = laserPos[i];
        float diff = abs(pos.x - lookPoint) - x0;
        if(diff < 0) diff = 0;
        ofPoint p;
        float rad = rotate * DEG_TO_RAD;
        p.y = (-pos.y + camHeight / 2) / RESOLUSION_HEIGHT * 25.4;
        p.z = - Lz * cos(rad) * (1 - Nx * d / (Nx * d + Lw * diff));
        p.x = Lz * sin(rad) * (1 - Nx * d / (Nx * d + Lw * diff));
//        pts.push_back(p);
    }
}