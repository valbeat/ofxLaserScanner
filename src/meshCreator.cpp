//
//  meshCreator.cpp
//  LaserScanner
//
//  Created by kajikawa on 2016/01/20.
//
//

#include "meshCreator.h"

MeshCreator::MeshCreator() {
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
//    mesh.enableTextures();
    header = 0;
}

void MeshCreator::setMode(ofPrimitiveMode _mode) {
    mesh.setMode(_mode);
}
ofVec3f MeshCreator::normal(ofVec3f _a, ofVec3f _b, ofVec3f _c) {
    ofVec3f v1 = _b - _a;
    ofVec3f v2 = _c - _a;
    ofVec3f cross = v1.crossed(v2);
    return cross.normalized();
}
void MeshCreator::save(string _name) {

}
void MeshCreator::draw(){
    mesh.draw();
}
void MeshCreator::clear() {
    mesh.clear();
    header = 0;
}
void MeshCreator::addSmoothPoint(vector<Point_Data> _data,ofVec2f _beginTex , ofVec2f _endTex, float _size){
    vector< vector<Polygon_Data> > polygon;
    vector<int> index;
    ofVec3f O(1000,1000,1000);
    float V;
    ofColor color(255,255,255);
    vector<Point_Data> pointData = _data;
    float incAngle = 360.0 / (divide + 1);
    if(pointData.size() < 1) return;
    int pointID = 0;
    
    // Mesh Dataの作成
    // Meshの追加
    
    // Indexの追加
    
}

// ドロネー分割でポリゴンを生成
void MeshCreator::createDelaunay(vector<ofPoint> _points) {
    if (_points.size() < 3) {
        return;
    }
    delaunay.reset();
    delaunay.addPoints(_points);
    delaunay.triangulate();
}