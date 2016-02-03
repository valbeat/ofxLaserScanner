//
//  guiManager.h
//  LaserScanner
//
//  Created by kajikawa on 2/3/16.
//
//

#ifndef guiManager_h
#define guiManager_h
#include "ofMain.h"
#include "ofxGui.h"

class GuiManager {
public:
    void setup();

private:
    bool guiFlag; // GUIを表示させるかどうか
    
    void paramsChanged();
    
    //GUI
    ofxPanel gui;
    ofxIntSlider laserBright;
    void onLaserBrightChanged(int &laserBright);
    ofxIntSlider distanceCameraLaser; // カメラとレーザーの距離[mm]
    void onDistanceCameraLaserChanged(int &distanceCameraLaser); // カメラとレーザーの距離を設定
    ofxIntSlider distanceCameraScreen; // カメラとスクリーンの距離[mm]
    void onDistanceCameraScreenChanged(int &disntanceCameraScreen); // カメラとスクリーンの距離を設定
    ofxIntSlider laserPointInterval; // レーザーポインタの間隔
    void onLaserPointInervalChanged(int &laserPointInterval); // レーザーポインタの間隔を設定
    ofxIntSlider rotate; // 回転角
    void onRotateChanged(int &rotate); // 回転角を設定
    ofxIntSlider rotateInterval; // 回転量
    void onRotateIntervalChanged(int &rotateInterval); // 回転量を設定
    ofxButton updateRotateButton; // 回転角を回転量分増やすボタン
    void onUpdateRotateButtonPressed(); // 回転角を増やすボタンのリスナー
    ofxButton resetPointsButton; // リセットボタン
    void onResetPointsButtonPressed(); // リセットボタンのリスナー
    ofxButton startScanButton; // スキャンスタートのボタン
    void onStartScanButtonPressed();
    ofxButton saveButton; // セーブボタン
    void onSaveButtonPressed();
    
    
    
};

#endif /* guiManager_h */
