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
#include "utility.h"
#include "laser.h"

// oFの解像度 [dpi]
#define RESOLUSION_WIDTH 72
#define RESOLUSION_HEIGHT 72

#define LASER_PIXELS 480 // ラインレーザーの最大値
#define MAX_ROTATE 360 // 回転の最大値
#define NUM_VERTEX LASER_PIXELS * MAX_ROTATE // 最大頂点

class LaserScanner {
public:

    bool useVideo = false;
    
    int width; // 幅
    int height; // 高さ
    
    // キャプチャした画像
    ofFbo image;
    // レーザー光があたっている場所
    ofFbo laserScan;

    
    int d; // カメラとレーザーの距離[mm]
    int Lz; // カメラとスクリーンの距離[mm]
    int laserPointInterval; // レーザーのy軸方向の間隔
    int rotate; // 回転角
    int rotateInterval; // 回転量
    

    // レーザーの座標を蓄えておく
    vector<ofVec3f> pts;
    
    // 3Dモデルのポイントクラウド
    ofMesh pointCloud;
    
    bool isStart;

    void setup(int w, int h);
    void setupPointCloud();
    void start();
    void update();
    void updateRotate();
    void setImage(ofFbo source);
    ofFbo getImage();
    void calc();
    void readLaserPixels(ofPixels pixels);
    void createPointCloud();
    void setRotate(int angle);
    
    int getCenter();
    
    void setLaserBrightness(int brightness);

    int x0;
    
private:
    Laser laser;
    vector<ofVec2f> laserPos;    // スクリーン上でレーザーが当たっている位置
    
    void drawLaserPoints(vector<ofVec2f> position);
    
};

#endif /* laserScanner_hpp */
