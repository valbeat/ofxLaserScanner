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
    static float mean(vector<int> v);
    static float median(vector<int> v);
    static string vecToCSV(vector<ofPoint> v);
    static void saveCSV(string fileName, vector<ofPoint> v);
private:
    Utility();
    
};

#endif /* Utility_h */
