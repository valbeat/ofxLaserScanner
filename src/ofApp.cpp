#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    #ifdef USE_LIVE_VIDEO
    videoSource.setupCamera(1, CAMERA_WIDTH, CAMERA_HEIGHT);
    #else
    videoSource.setupVideo(VIDEO_NAME, CAMERA_WIDTH, CAMERA_HEIGHT);
    #endif
    
    laserScanner.setup(CAMERA_WIDTH, CAMERA_HEIGHT);
    
    setupGui();
    setupPreviewCamera();

    preview.allocate(laserScanner.width, laserScanner.height, GL_RGB);
    preview.begin();
    ofClear(0,255);
    preview.end();
    
    setLaserScannerParams();
    
    

    
//    vbo.setVertexData(pts,NUM_VERTEX, GL_DYNAMIC_DRAW);
    

    
    // マウスカーソル非表示バグ回避
    ofHideCursor();
    
//    serial.setup(SERIAL_PORT,9600);
    
}
//--------------------------------------------------------------
void ofApp::update(){
    // 画像のアップデートができていない場合は更新しない
    if (!videoSource.update()) return;
    // レーザースキャナに画像読み込ませる
    ofFbo source = videoSource.getImage();
    laserScanner.setImage(source);
    // レーザースキャナの更新
    laserScanner.update();

    // 点群データの作成
    laserScanner.createPointCloud();

    // プレビュー画面の作成
    preview.begin();
    ofClear(0);
    previewCamera.begin();
    laserScanner.pointCloud.draw();
    previewCamera.end();
    preview.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    videoSource.getImage().draw(0,0,CAMERA_WIDTH,CAMERA_HEIGHT);

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255,100);
    laserScanner.getImage().draw(0,0,CAMERA_WIDTH,CAMERA_HEIGHT);
    ofDisableBlendMode();
    
//    glEnable(GL_POINT_SMOOTH);
//    glPointSize(3);
    ofEnableDepthTest();
    ofSetColor(255);
    preview.draw(CAMERA_WIDTH,0,CAMERA_WIDTH,CAMERA_HEIGHT);
    ofDisableDepthTest();
//    glDisable(GL_POINT_SMOOTH);
    
    ofSetColor(255, 0, 0);
    ofRect(CAMERA_WIDTH / 2 - laserScanner.x0 , 0, 1, CAMERA_HEIGHT);
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

void ofApp::setupPreviewCamera() {
    previewCamera.setNearClip(1e-4);
    previewCamera.setFarClip(1000);
    previewCamera.setDistance(0);
    previewCamera.setPosition(0,0,-100);
    previewCamera.lookAt(ofVec3f(0,0,1));
}

//--------------------------------------------------------------
void ofApp::setupGui() {
    
    guiFlag = true;
    gui.setup();
    gui.add(laserBright.setup("laserBright",250,0,255));
    laserBright.addListener(this, &ofApp::onLaserBrightChanged);
    
    gui.add(distanceCameraLaser.setup("d(mm)", 60, 0, 200));
    distanceCameraLaser.addListener(this, &ofApp::onDistanceCameraLaserChanged);
    
    gui.add(distanceCameraScreen.setup("Lz(mm)", 260, 0, 1000));
    distanceCameraScreen.addListener(this, &ofApp::onDistanceCameraScreenChanged);
    
    gui.add(laserPointInterval.setup("laser Interval", 5,1,10));
    laserPointInterval.addListener(this, &ofApp::onLaserPointInervalChanged);
    
    gui.add(rotate.setup("theta",0,0,360));
    rotate.addListener(this, &ofApp::onRotateChanged);
    
    gui.add(rotateInterval.setup("rotateInterval",1,1,90));
    rotateInterval.addListener(this, &ofApp::onRotateIntervalChanged);
    
    gui.add(updateRotateButton.setup("theta += rotateInterval"));
    updateRotateButton.addListener(this, &ofApp::onUpdateRotateButtonPressed);
    
    gui.add(startScanButton.setup("start"));
    startScanButton.addListener(this, &ofApp::onStartScanButtonPressed);
    
    gui.add(resetPointsButton.setup("reset"));
    resetPointsButton.addListener(this, &ofApp::onResetPointsButtonPressed);
    
    gui.add(saveButton.setup("save"));
    saveButton.addListener(this, &ofApp::onSaveButtonPressed);
    
    
    gui.loadFromFile("settings.xml");
    
}

void ofApp::setLaserScannerParams() {
    laserScanner.setLaserBrightness(laserBright);
    laserScanner.d = distanceCameraLaser;
    laserScanner.Lz = distanceCameraScreen;
    laserScanner.laserPointInterval = laserPointInterval;
    laserScanner.rotate = rotate;
    laserScanner.rotateInterval = rotateInterval;
}

void ofApp::onLaserBrightChanged(int &laserBright) {
    laserScanner.setLaserBrightness(laserBright);
}
//--------------------------------------------------------------
void ofApp::onDistanceCameraLaserChanged(int &distanceCameraLaser) {
    laserScanner.d = distanceCameraLaser;
}
//--------------------------------------------------------------
void ofApp::onDistanceCameraScreenChanged(int &distanceCameraScreen) {
    laserScanner.Lz = distanceCameraScreen;
}
//--------------------------------------------------------------
void ofApp::onLaserPointInervalChanged(int &laserPointInterval) {
    laserScanner.laserPointInterval = laserPointInterval;
}
//--------------------------------------------------------------
void ofApp::onRotateChanged(int &rotate){
    laserScanner.rotate = rotate;
}
//--------------------------------------------------------------
void ofApp::onRotateIntervalChanged(int &rotateInterval) {
    laserScanner.rotateInterval = rotateInterval;
}
//--------------------------------------------------------------
void ofApp::onUpdateRotateButtonPressed() {
    laserScanner.updateRotate();
}
//--------------------------------------------------------------
void ofApp::onStartScanButtonPressed() {
    bool isStart = laserScanner.isStart;
    isStart ? isStart = false : isStart = true;
    laserScanner.isStart = isStart;
}
//--------------------------------------------------------------
void ofApp::onResetPointsButtonPressed() {
    laserScanner.pts.clear();
    laserScanner.isStart = false;
    rotate = 0;
}
//--------------------------------------------------------------
void ofApp::onSaveButtonPressed() {
    saveCSV(laserScanner.pts);
}
//--------------------------------------------------------------
// CSVに保存する
void ofApp::saveCSV(vector<ofPoint> v) {
    string s = Utility::vecToCSV(v);
    ofBuffer buffer = s;
    ofBufferToFile(CSV_NAME, buffer);
}
//--------------------------------------------------------------