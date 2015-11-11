#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();
    
    camera.listDevices();
    camera.setVerbose(true);
    camera.setDeviceID(0);
    camera.initGrabber(camWidth,camHeight);
    
    
    gui.setup();
    gui.add(laserBright.setup("laserBright",220,0,250));
    gui.add(d.setup("d(mm)", 5, 0, 20));
    gui.add(l.setup("L(mm)", 20, 0, 500));
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.draw(0, 0, camWidth, camHeight);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
