#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    #ifdef _USE_LIVE_VIDEO
    setupCamera();
    #else
    setupVideo();
    #endif
    setupGui();
    capture.allocate(camWidth, camHeight, GL_RGB);
    laserScan.allocate(camWidth, camHeight, GL_RGB);
    // マウスカーソル非表示バグ回避
    ofHideCursor();

}
//--------------------------------------------------------------
void ofApp::update(){
    bool isNewFrame = false;
    #ifdef _USE_LIVE_VIDEO
    camera.update();
    isNewFrame = camera.isFrameNew();
    #else
    video.update();
    isNewFrame = video.isFrameNew();
    #endif
    if (isNewFrame) {
        #ifdef _USE_LIVE_VIDEO
        capture.begin();
        camera.draw(0,0, camWidth, camHeight);
        capture.end();
        #else
        capture.begin();
        video.draw(0, 0, camWidth, camHeight);
        capture.end();
        #endif

        ofPixels pixels;
        capture.readToPixels(pixels);
        readLaserPixels(pixels);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    laserScan.draw(0,0,camWidth,camHeight);
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
    //マウスカーソル非表示バグ回避
    ofShowCursor();
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
    camera.setDesiredFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
    camera.setVerbose(true);
    camera.listDevices();
    camera.setDeviceID(0);
    camera.initGrabber(camWidth,camHeight);
}
void ofApp::setupVideo() {
    camWidth = 640;
    camHeight = 480;
    video.loadMovie(VIDEO_NAME);
    video.play();
}
void ofApp::setupGui() {
    guiFlag = true;
    gui.setup();
    gui.add(laserBright.setup("laserBright",220,0,250));
    gui.add(d.setup("d(mm)", 5, 0, 20));
    gui.add(L.setup("L(mm)", 20, 0, 500));
    gui.loadFromFile("settings.xml");
}
void ofApp::readLaserPixels(ofPixels pixels) {
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    laserScan.begin();
    for (int y = 0; y < h; y+= 10) {
        for (int x = 0; x < w ; x++) {
            ofColor c = pixels.getColor(x, y);
            if(c.g > laserBright) {
                ofSetColor(0,255,0);
                ofRect(x, y, 1, 1);
            }
        }
    }
    laserScan.end();
}

void ofApp::calc() {
    int x0;
    int Nx = camWidth; // スクリーン幅
    float Lw; //
    int lookPoint = (int)(camWidth / 2); // 注視点（カメラの中心）
    // dの[mm]→[pixel]変換
    x0 = (int)(d * 72 / 25.4);
}