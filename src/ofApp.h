#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCsv.h"

#


#undef USE_LIVE_CAMERA
#define VIDEO_NAME "test.mov"

// シリアルポート
#define SERIAL_PORT "/dev/tty.usbmodem1411"

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
    // 3Dモデルをポイントクラウドで表示
    ofMesh pointCloud;
    
    //GUI
    ofxPanel gui;
    ofxIntSlider laserBright;
    ofxIntSlider d; // カメラとレーザーの距離[mm]
    ofxIntSlider Lz; // カメラとスクリーンの距離[mm]
    ofxIntSlider laserPointInterval; // レーザーポインタの間隔
    ofxIntSlider rotate; // 回転角
    ofxIntSlider rotateInterval; // 回転量
    ofxButton updateRotateButton; // 回転角を回転量分増やすボタン
    void updateRotateButtonPressed(); // 回転角を増やすボタンの関数
    ofxButton resetPointsButton;
    void resetPointsButtonPressed();
    ofxButton startScanButton;
    void startScanButtonPressed();
    ofxButton saveButton;
    void saveButtonPressed();
    
    void updateRotate();
    
    ofEasyCam cam3d;
    
    bool debugFlag;
    bool guiFlag;

    void createPointCloud();
    void setupGui();
    void setupCam3d();
    void saveCSV(vector<ofPoint>);
    
    // vbo
    ofVbo vbo;
    // レーザーの座標を蓄えておく
    vector<ofPoint> pts;
    // 現在のフレームの座標
    vector<ofPoint> pts_temp;
    
    void setRotate(int angle);
    
    float mean(vector<int>);
    float median(vector<int>);
    

    ofFile csvFile;
    
    ofSerial serial;
    
    string vecToCSV(vector<ofPoint>);
};
