#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    setupCamera();
    setupGui();
    capture.allocate(camWidth, camHeight, GL_RGB);

}
//--------------------------------------------------------------
void ofApp::update(){
    bool isNewFrame = false;
    camera.update();
    isNewFrame = camera.isFrameNew();
    
    if (isNewFrame) {
        capture.begin();
        capture.draw(0,0, capture.getWidth(), capture.getHeight());
        capture.end();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    capture.draw(0, 0, camWidth, camHeight);
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
void ofApp::setupCamera() {
    camWidth = 640;
    camHeight = 480;
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    camera.setVerbose(true);
    camera.listDevices();
    camera.setDeviceID(0);
    camera.initGrabber(camWidth,camHeight);
}
void ofApp::setupGui() {
    guiFlag = true;
    gui.setup();
    gui.add(laserBright.setup("laserBright",220,0,250));
    gui.add(d.setup("d(mm)", 5, 0, 20));
    gui.add(L.setup("L(mm)", 20, 0, 500));
    gui.loadFromFile("settings.xml");
}
void ofApp::getLaserPixel(ofImage image) {
    ofPixels pixels = image.getPixelsRef();
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w ; x++) {
            ofColor color = pixels.getColor(x, y);
            if (color.g > laserBright) {
                ofPushMatrix();
                ofSetColor(0, 255, 0);
                ofRect(x, y, 1, 1);
                ofPopMatrix();
            }
        }
    }
}

void ofApp::calc() {
    int x0;
    int Nx = camWidth; // スクリーン幅
    float Lw; //
    int lookPoint = (int)(camWidth / 2); // 注視点（カメラの中心）
    // dの[mm]→[pixel]変換
    x0 = (int)(d * 72 / 25.4);
    
}