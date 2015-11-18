#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//#define _USE_LIVE_VIDEO
#define VIDEO_NAME "test.mov"

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

    

    //ライブカメラを使用する際には、カメラ入力を準備
    ofVideoGrabber camera;
    void setupCamera();
    //あらかじめ録画した映像を使用する際には、ビデオプレイヤーを準備
    ofVideoPlayer video;
    void setupVideo();
    
    int camWidth;
    int camHeight;
    
    ofFbo capture;
    ofFbo laserScan;
    
    //GUI
    ofxPanel gui;
    ofxIntSlider laserBright;
    ofxFloatSlider d; // カメラとレーザーの距離
    ofxFloatSlider L; // カメラとスクリーンの距離
    
    bool debugFlag;
    bool guiFlag;

    void findLineCenter();
    void calc();
    void readLaserPixels(ofPixels pixels);
    void setupGui();
    
};
