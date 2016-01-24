
#ifndef camera_h
#define camera_h
#include "ofMain.h"

// スキャナーに読み込ませる画像を管理
class VideoSource {
    
public:
    
    int width; // 幅
    int height; // 高さ
    
    bool useVideo;
    bool isNewFrame();

    void setupCamera(int id, int w, int h); // カメラを使う時のセットアップ
    void setupVideo(string name, int w, int h); // 動画を使う時のセットアップ
    void setupImage(); // 取得画像の初期設定
    
    bool update(); // 画像の更新
    
    ofFbo getImage();
    
private:
    //ライブカメラを使用する際には、カメラ入力を準備
    ofVideoGrabber camera;
    
    //あらかじめ録画した映像を使用する際には、ビデオプレイヤーを準備
    ofVideoPlayer video;
    
    // カメラまたは動画から取得した画像
    ofFbo image;
};


#endif /* camera_h */
