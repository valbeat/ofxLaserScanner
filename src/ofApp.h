#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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

    //カメラ
    ofVideoGrabber camera;
    int camWidth;
    int camHeight;
    
    ofFbo capture;
    
    //GUI
    ofxPanel gui;
    ofxIntSlider laserBright;
    ofxFloatSlider d; // カメラとレーザーの距離
    ofxFloatSlider L; // カメラとスクリーンの距離

    bool guiFlag;

    void findLineCenter();
    void calc();
    void setLaserPixel(ofPixels &pixels);
    void setupCamera();
    void setupGui();
    
};
