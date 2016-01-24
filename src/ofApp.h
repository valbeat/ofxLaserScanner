#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCsv.h"

#include "laserScanner.h"
#include "videoSource.h"
#include "utility.h"



#undef USE_LIVE_CAMERA

// csv書き出し用ファイル
#define CSV_NAME "data.csv"

// カメラのID
#define CAMERA_ID 1

// デバッグ用に使う動画
#define VIDEO_NAME "test.mov"

// シリアルポート
#define SERIAL_PORT "/dev/tty.usbmodem1411"

// カメラのサイズ設定
#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// エントリーポイント
class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // 3Dモデルプレビュー
    ofFbo preview;
    
    //GUI
    ofxPanel gui;
    ofxIntSlider laserBright;
    void setLaserBright();
    ofxIntSlider d; // カメラとレーザーの距離[mm]
    void setD(); // カメラとレーザーの距離を設定
    ofxIntSlider Lz; // カメラとスクリーンの距離[mm]
    void setLz(); // カメラとスクリーンの距離を設定
    ofxIntSlider laserPointInterval; // レーザーポインタの間隔
    void setLaserPointInerval(); // レーザーポインタの間隔を設定
    ofxIntSlider rotate; // 回転角
    void setRotate(); // 回転角を設定
    ofxIntSlider rotateInterval; // 回転量
    void setRotateInterval(); // 回転量を設定
    ofxButton updateRotateButton; // 回転角を回転量分増やすボタン
    void updateRotateButtonPressed(); // 回転角を増やすボタンの関数
    ofxButton resetPointsButton;
    void resetPointsButtonPressed();
    ofxButton startScanButton;
    void startScanButtonPressed();
    ofxButton saveButton;
    void saveButtonPressed();

    
    ofEasyCam cam3d;
    
    bool debugFlag;
    bool guiFlag;

    void createPointCloud();
    void setupGui();
    void setupCam3d();
    void saveCSV(vector<ofPoint>);
    
    // vbo
    ofVbo vbo;

    ofFile csvFile;
    
    ofSerial serial;
    
    VideoSource videoSource;
    LaserScanner laserScanner;
};
