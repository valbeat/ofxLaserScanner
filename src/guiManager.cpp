#include "guiManager.h"

void GuiManager::setup() {
    guiFlag = true;
    gui.setup();
    gui.add(laserBright.setup("laserBright",250,0,255));
    laserBright.addListener(this, &GuiManager::onLaserBrightChanged);
    
    gui.add(distanceCameraLaser.setup("d(mm)", 60, 0, 200));
    distanceCameraLaser.addListener(this, &GuiManager::onDistanceCameraLaserChanged);
    
    gui.add(distanceCameraScreen.setup("Lz(mm)", 260, 0, 1000));
    distanceCameraScreen.addListener(this, &GuiManager::onDistanceCameraScreenChanged);
    
    gui.add(laserPointInterval.setup("laser Interval", 5,1,10));
    laserPointInterval.addListener(this, &GuiManager::onLaserPointInervalChanged);
    
    gui.add(rotate.setup("theta",0,0,360));
    rotate.addListener(this, &GuiManager::onRotateChanged);
    
    gui.add(rotateInterval.setup("rotateInterval",1,1,90));
    rotateInterval.addListener(this, &GuiManager::onRotateIntervalChanged);
    
    gui.add(updateRotateButton.setup("theta += rotateInterval"));
    updateRotateButton.addListener(this, &GuiManager::onUpdateRotateButtonPressed);
    
    gui.add(startScanButton.setup("start"));
    startScanButton.addListener(this, &GuiManager::onStartScanButtonPressed);
    
    gui.add(resetPointsButton.setup("reset"));
    resetPointsButton.addListener(this, &GuiManager::onResetPointsButtonPressed);
    
    gui.add(saveButton.setup("save"));
    saveButton.addListener(this, &GuiManager::onSaveButtonPressed);
    
    gui.loadFromFile("settings.xml");

}


void GuiManager::onLaserBrightChanged(int &laserBright) {
//    laserScanner.setLaserBrightness(laserBright);
}
//--------------------------------------------------------------
void GuiManager::onDistanceCameraLaserChanged(int &distanceCameraLaser) {
//    laserScanner.d = distanceCameraLaser;
}
//--------------------------------------------------------------
void GuiManager::onDistanceCameraScreenChanged(int &distanceCameraScreen) {
//    laserScanner.Lz = distanceCameraScreen;
}
//--------------------------------------------------------------
void GuiManager::onLaserPointInervalChanged(int &laserPointInterval) {
//    laserScanner.laserPointInterval = laserPointInterval;
}
//--------------------------------------------------------------
void GuiManager::onRotateChanged(int &rotate){
//    laserScanner.rotate = rotate;
}
//--------------------------------------------------------------
void GuiManager::onRotateIntervalChanged(int &rotateInterval) {
//    laserScanner.rotateInterval = rotateInterval;
}
//--------------------------------------------------------------
void GuiManager::onUpdateRotateButtonPressed() {
//    laserScanner.updateRotate();
}
//--------------------------------------------------------------
void GuiManager::onStartScanButtonPressed() {
//    bool isStart = laserScanner.isStart;
//    isStart ? isStart = false : isStart = true;
//    laserScanner.isStart = isStart;
}
//--------------------------------------------------------------
void GuiManager::onResetPointsButtonPressed() {
//    laserScanner.pts.clear();
//    laserScanner.isStart = false;
//    rotate = 0;
}
//--------------------------------------------------------------
void GuiManager::onSaveButtonPressed() {
//    saveCSV(CSV_NAME,laserScanner.pts);
}