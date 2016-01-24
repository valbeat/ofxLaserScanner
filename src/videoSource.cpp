#include "videoSource.h"

//--------------------------------------------------------------
bool VideoSource::isNewFrame() {
    bool isNewFrame = false;
    if (!useVideo) {
        camera.update();
        isNewFrame = camera.isFrameNew();
    } else {
        video.update();
        isNewFrame = video.isFrameNew();
    }
    return isNewFrame;
}
//--------------------------------------------------------------
bool VideoSource::update() {
    if (!isNewFrame()) {
        return false;
    }
    if (!useVideo) {
        image.begin();
        camera.draw(0,0, width, height);
        image.end();
    } else {
        image.begin();
        video.draw(0, 0, width, height);
        image.end();
    }
    return true;
}
//--------------------------------------------------------------
void VideoSource::setupImage() {
    image.allocate(width, height, GL_RGB);
    image.begin();
    ofClear(0,255);
    image.end();
}
//--------------------------------------------------------------
void VideoSource::setupCamera(int id, int w, int h) {
    width = w;
    height = h;
    camera.setDesiredFrameRate(30);
    ofSetLogLevel(OF_LOG_VERBOSE);
    camera.setVerbose(true);
    camera.listDevices();
    camera.setDeviceID(id);
    camera.initGrabber(width,height);
    useVideo = false;
    setupImage();
}
//--------------------------------------------------------------
void VideoSource::setupVideo(string name, int w, int h) {
    width = w;
    height = h;
    video.loadMovie(name);
    video.play();
    useVideo = true;
    setupImage();
}
//--------------------------------------------------------------
ofFbo VideoSource::getImage() {
    return image;
}
