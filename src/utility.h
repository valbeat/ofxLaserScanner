//
//  Utility.h
//  LaserScanner
//
//  Created by kajikawa on 2016/01/21.
//
//

#ifndef Utility_h
#define Utility_h
#include "ofMain.h"

// 共通クラス
class Utility {
public:
    float mean(vector<int> v);
    float median(vector<int> v);
    string vecToCSV(vector<ofPoint> v);
};

#endif /* Utility_h */
