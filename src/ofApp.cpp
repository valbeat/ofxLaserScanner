#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    camWidth = 640;
    camHeight = 480;
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    camera.setVerbose(true);
    camera.listDevices();
    camera.setDeviceID(0);
    camera.initGrabber(camWidth,camHeight);
    
    guiFlag = true;
    gui.setup();
    gui.add(laserBright.setup("laserBright",220,0,250));
    gui.add(d.setup("d(mm)", 5, 0, 20));
    gui.add(L.setup("L(mm)", 20, 0, 500));
    
    fbo.allocate(camWidth, camHeight, GL_RGB);
    
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    bool isNewFrame = false;
    camera.update();
    isNewFrame = camera.isFrameNew();
    
    if (isNewFrame) {
        fbo.begin();
        camera.draw(0,0, fbo.getWidth(), fbo.getHeight());
        fbo.end();
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    fbo.draw(0, 0, camWidth, camHeight);
    if (guiFlag)
        gui.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'g' :
            (guiFlag == false) ? guiFlag = true : guiFlag = false;
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::calc() {
    int x0;
    int Nx = camWidth; // スクリーン幅
    float Lw; //
    int lookPoint = (int)(camWidth / 2); // 注視点（カメラの中心）
    // dの[mm]→[pixel]変換
    x0 = (int)(d * 72 / 25.4);
    
}