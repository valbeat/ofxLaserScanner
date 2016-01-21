#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    #ifdef USE_LIVE_VIDEO
        setupCamera();
    #else
        setupVideo();
    #endif
    
    setupGui();
    setupCam3d();
    
    image.allocate(camWidth, camHeight, GL_RGB);
    image.begin();
    ofClear(0,255);
    image.end();
    
    laserScan.allocate(camWidth, camHeight, GL_RGB);
    laserScan.begin();
    ofClear(0,255);
    laserScan.end();
    
    preview.allocate(camWidth, camHeight, GL_RGB);
    preview.begin();
    ofClear(0,255);
    preview.end();
    
    
//    vbo.setVertexData(pts,NUM_VERTEX, GL_DYNAMIC_DRAW);
    
    pointCloud.clearVertices();
    pointCloud.setMode(OF_PRIMITIVE_POINTS);
    
    // マウスカーソル非表示バグ回避
    ofHideCursor();
    
    serial.setup(SERIAL_PORT,9600);
    
}
//--------------------------------------------------------------
void ofApp::update(){
    bool isNewFrame = false;
    #ifdef USE_LIVE_VIDEO
    camera.update();
    isNewFrame = camera.isFrameNew();
    #else
    video.update();
    isNewFrame = video.isFrameNew();
    #endif
    if (isNewFrame) {
        #ifdef USE_LIVE_VIDEO
        image.begin();
        camera.draw(0,0, camWidth, camHeight);
        image.end();
        #else
        image.begin();
        video.draw(0, 0, camWidth, camHeight);
        image.end();
        #endif
        
        if (isStart) {
            updateRotate();
        }
        
        ofPixels pixels;
        image.readToPixels(pixels);
        readLaserPixels(pixels);
        
        calc();
        
        createPointCloud();

        preview.begin();
        ofClear(0);
        cam3d.begin();
        pointCloud.draw();
        cam3d.end();
        preview.end();
        
        laserPos.clear();

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    image.draw(0, 0, camWidth, camHeight);

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255,100);
    laserScan.draw(0,0,camWidth,camHeight);
    ofDisableBlendMode();
    
//    glEnable(GL_POINT_SMOOTH);
//    glPointSize(3);
    ofEnableDepthTest();
    ofSetColor(255);
    preview.draw(camWidth,0,camWidth,camHeight);
    ofDisableDepthTest();
//    glDisable(GL_POINT_SMOOTH);
    
    ofSetColor(255, 0, 0);
    ofRect(camWidth / 2 - x0, 0, 1, camHeight);
    ofSetColor(255);
    
    
    if (guiFlag) {
        ofSetColor(255);
        gui.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'g' :
            (guiFlag == false) ? guiFlag = true : guiFlag = false;
            break;
        case 'f':
            ofToggleFullscreen();
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

void ofApp::setupCam3d() {
    cam3d.setNearClip(1e-4);
    cam3d.setFarClip(1000);
    cam3d.setDistance(0);
    cam3d.setPosition(0,0,-100);
    cam3d.lookAt(ofVec3f(0,0,1));
}

//--------------------------------------------------------------
void ofApp::setupGui() {
    //ボタンの動作設定
    updateRotateButton.addListener(this, &ofApp::updateRotateButtonPressed);
    resetPointsButton.addListener(this, &ofApp::resetPointsButtonPressed);
    startScanButton.addListener(this, &ofApp::startScanButtonPressed);
    saveButton.addListener(this, &ofApp::saveButtonPressed);
    
    guiFlag = true;
    gui.setup();
    gui.add(laserBright.setup("laserBright",250,0,255));
    gui.add(d.setup("d(mm)", 60, 0, 200));
    gui.add(Lz.setup("Lz(mm)", 260, 0, 1000));
    gui.add(laserPointInterval.setup("laser Interval", 5,1,10));
    gui.add(rotate.setup("theta",0,0,360));
    gui.add(rotateInterval.setup("rotateInterval",1,1,90));
    gui.add(updateRotateButton.setup("theta += rotateInterval"));
    gui.add(startScanButton.setup("start"));
    gui.add(resetPointsButton.setup("reset"));
    gui.add(saveButton.setup("save"));
    gui.loadFromFile("settings.xml");
    
}
//--------------------------------------------------------------
void ofApp::updateRotate() {
    int r = rotate;
    if (r >= 360) {
        isStart = false;
        return;
    }
    r += rotateInterval;
    if (r > 359) r = 359;
    rotate = r;
}
//--------------------------------------------------------------
void ofApp::updateRotateButtonPressed() {
    updateRotate();
}
//--------------------------------------------------------------
void ofApp::startScanButtonPressed() {
    isStart ? isStart = false : isStart = true;
}
//--------------------------------------------------------------
void ofApp::resetPointsButtonPressed() {
    pts.clear();
    isStart = false;
    rotate = 0;
}

//--------------------------------------------------------------
void ofApp::saveButtonPressed() {
    saveCSV(pts);
}
//--------------------------------------------------------------
void ofApp::readLaserPixels(ofPixels pixels) {
    laserScan.begin();
    ofClear(0,255);
    laserScan.end();
    int w = pixels.getWidth();
    int h = pixels.getHeight();

    for (int y = 0; y < h; y+= laserPointInterval) {
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
            
            // レーザーの中心を表示させる
            laserScan.begin();
            // ブレンドモードをONにした時はスムージングを切る
            ofDisableSmoothing();
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(0,255,0);
            ofRect(mX - 1, y, 2, 2);
            ofSetColor(255, 255, 255);
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            laserScan.end();
        }
    }
}
//--------------------------------------------------------------
// ポイントクラウド生成
void ofApp::createPointCloud() {
    if (pts.empty()) {
        return;
    }
    pointCloud.clear();
    for (int i = 0; i < pts.size(); i++) {
        ofPoint pos = pts[i];
        pointCloud.addVertex(pos);
    }
}

//--------------------------------------------------------------
// CSVに保存する
void ofApp::saveCSV(vector<ofPoint> v) {
    string s = Utility::vecToCSV(v);
    ofBuffer buffer = s;
    ofBufferToFile("data.csv", buffer);
}
//--------------------------------------------------------------