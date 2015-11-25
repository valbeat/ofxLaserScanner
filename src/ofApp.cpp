#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofBackground(0, 0, 0);
    #ifdef _USE_LIVE_VIDEO
    setupCamera();
    #else
    setupVideo();
    #endif
    setupGui();
    capture.allocate(camWidth, camHeight, GL_RGB);
    capture.begin();
    ofClear(0,255);
    ofRect(0, 0, camWidth, camHeight);
    capture.end();
    laserScan.allocate(camWidth, camHeight, GL_RGB);
    laserScan.begin();
    ofClear(0,255);
//    ofRect(0, 0, camWidth, camHeight);
    laserScan.end();
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
    ofSetColor(255);
    capture.draw(0, 0, camWidth, camHeight);
    ofSetColor(255,100);
    laserScan.draw(0,0,camWidth,camHeight);
    
    if (!laserPos.empty()) {
        for (int i = 0; i < laserPos.size(); i++) {
            ofPoint pos = laserPos[i];
            cout <<  "i:" << i << " x:" << pos.x << " y:" << pos.y << endl;
            ofSetColor(255);
        }
        laserPos.clear();
    }
    
    
    if (guiFlag)
        ofSetColor(255);
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
    gui.add(d.setup("d(mm)", 5, 0, 200));
    gui.add(L.setup("L(mm)", 20, 0, 1000));
    gui.loadFromFile("settings.xml");
}
void ofApp::readLaserPixels(ofPixels pixels) {
    laserScan.begin();
    ofClear(0,255);
    laserScan.end();
    int w = pixels.getWidth();
    int h = pixels.getHeight();

    for (int y = 0; y < h; y+= 10) {
        vector<int> v;
        for (int x = 0; x < w ; x++) {
            ofColor c = pixels.getColor(x, y);
            if(c.g > laserBright) {
                v.push_back(x);
            }
        }
        
        if (!v.empty()) {
            int mX = (int)median(v);
            laserPos.push_back(ofPoint(mX,y));
            laserScan.begin();
            ofDisableSmoothing();
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(0,255,0);
            ofRect(mX, y, 1, 1);
            ofSetColor(255, 255, 255);
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            laserScan.end();
        }
    }
}

ofPoint ofApp::calc(ofPoint pos) {
    int x0;
    int Nx = camWidth; // スクリーン幅
    float Lw; //
    int lookPoint = (int)(camWidth / 2); // 注視点（カメラの中心）
    // dの[mm]→[pixel]変換
    x0 = (int)(d * RESOLUSION_WIDTH / 25.4);
    
    Lw = Nx / RESOLUSION_WIDTH * 25.4;
    float diff = abs(pos.x - lookPoint) - d;
    float Xs,Ys,Zs;
    ofPoint point3d;
    point3d.z = -L * cos(rot) * (1 - Nx * d + Lw * diff);
    point3d.x = L * sin(rot) * (1 - Nx * d + Lw * diff);
    point3d.y = (-pos.y + 240) / RESOLUSION_HEIGHT;
    return point3d;
}

// 配列の平均値を返す
float ofApp::mean(vector<int> v) {
    int size = v.size();
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += v[i];
    }
    return sum / size;
}

// 配列の中央値を返す
float ofApp::median(vector<int> v) {
    int size = v.size();
    vector<int> _v;
    copy(v.begin(), v.end(), back_inserter(_v));
    int tmp;
    for (int i = 0; i < size - 1; i++){
        for (int j = i + 1; j < size; j++) {
            if (_v[i] > _v[j]){
                tmp = _v[i];
                _v[i] = _v[j];
                _v[j] = tmp;
            }
        }
    }
    if (size % 2 == 1) {
        return _v[(size - 1) / 2];
    } else {
        return (_v[(size / 2) - 1] + _v[size / 2]) / 2;
    }
}