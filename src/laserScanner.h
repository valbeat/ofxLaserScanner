//
//  laserScanner.hpp
//  LaserScanner
//
//  Created by kajikawa on 2016/01/20.
//
//

#ifndef laserScanner_h
#define laserScanner_h
#include "ofMain.h"

// oFの解像度 [dpi]
#define RESOLUSION_WIDTH 72
#define RESOLUSION_HEIGHT 72

#define LASER_PIXELS 480 // ラインレーザーの最大値
#define MAX_ROTATE 360 // 回転の最大値
#define NUM_VERTEX LASER_PIXELS * MAX_ROTATE // 最大頂点

class LaserScanner {
public:
    //ライブカメラを使用する際には、カメラ入力を準備
    ofVideoGrabber camera;
    void setupCamera();
    //あらかじめ録画した映像を使用する際には、ビデオプレイヤーを準備
    ofVideoPlayer video;
    void setupVideo(string videoName);
    
    int camWidth;
    int camHeight;
    
    // ビデオまたはカメラからキャプチャした画像
    ofFbo image;
    // レーザー光があたっている場所
    ofFbo laserScan;
    
    void calc();
    void readLaserPixels(ofPixels pixels);
    
    int laserBright; // レーザーの明るさ閾値
    int d; // カメラとレーザーの距離[mm]
    int Lz; // カメラとスクリーンの距離[mm]
    int laserPointInterval; // レーザーポインタの間隔
    int rotate; // 回転角
    int rotateInterval; // 回転量
    
    // スクリーン上でレーザーが当たっている位置
    vector<ofVec3f> laserPos;
    
    bool isStart;
    
private:
    int x0;
    
    
};

#endif /* laserScanner_hpp */
