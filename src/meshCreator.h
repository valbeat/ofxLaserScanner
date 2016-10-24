//
//  meshCreator.h
//  LaserScanner
//
//

#ifndef MeshCreator_h
#define MeshCreator_h
#include "ofMain.h"
#include "ofxDelaunay.h"

#define DIV_TRI 64

typedef struct {
    ofVec3f position;
    float size;
} Point_Data;

typedef struct {
    ofVec3f vert;
    ofVec3f norm;
    ofVec2f tex;
    ofFloatColor color;
} Polygon_Data;

class MeshCreator {
    
public:
    MeshCreator();
    
    void setMode(ofPrimitiveMode _mode);
    void draw();
    
    void addSmoothPoint(vector<Point_Data> _data,ofVec2f _beginTex,ofVec2f _endTex,float _size);
    
    void clear();
    void save(string _name);
    
    ofVec3f normal(ofVec3f _a,ofVec3f _b,ofVec3f _c);
    
    int divide = DIV_TRI;
    
    ofMesh mesh;

protected:
   int header = 0;
    
private:
    //ドロネー分割の結果
    ofxDelaunay delaunay;
    // ドロネー分割でメッシュを生成する
    // 頂点数が多すぎて使えない?
    void createDelaunay(vector<ofPoint> _points);
    
};

#endif /* meshCreator_h */