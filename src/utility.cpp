//
//  Utility.cpp
//  LaserScanner
//
//

#include "utility.h"

//--------------------------------------------------------------
// 配列の平均値を返す
float Utility::mean(vector<int> v) {
    int size = v.size();
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += v[i];
    }
    return sum / size;
}
//--------------------------------------------------------------
// 配列の中央値を返す
float Utility::median(vector<int> v) {
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
//--------------------------------------------------------------
// カンマ区切りの文字列を生成
string Utility::vecToCSV(vector<ofPoint> v) {
    std::stringstream ss;
    for (size_t i = 0; i < v.size(); ++i){
        ss << v[i].x << ',' << v[i].y << ',' << v[i].z;
        ss << '\n';
    }
    std::string s = ss.str();
    return s;
}

//--------------------------------------------------------------
// CSVファイルに保存する
void Utility::saveCSV(string fileName,vector<ofPoint> v) {
    string s = Utility::vecToCSV(v);
    ofBuffer buffer = s;
    ofBufferToFile(fileName, buffer);
}