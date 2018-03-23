#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void rossler(float a,float b,float c,float scale,int count,float* weight);
    
    void aChanged(float & a);
    void bChanged(float & b);
    void cChanged(float & c);
    void scaleChanged(float & a);
    void countChanged(int & count);
    void colorChanged(float & w);
    
    float x,y,z;
    float xn,yn,zn;
    
    ofParameter<int> count;
    ofParameter<float> a,b,c,scale;
    ofParameter<float> w_r,w_b,w_g;
    ofxPanel gui;
    ofFloatColor col;
//    ofParameter<float> w[3];
    float w[3];
    
    float r,g,bl;
    
    float rotate_x = 0;
    float rotate_y = 0;
    
    vector<ofVec3f> points;
    vector<ofIndexType> indices;
    vector<ofFloatColor> Color;
    ofEasyCam cam;
    ofVbo vbo;
    
    bool bRotate=true;
    bool bF1=false;
    bool showGui=true;
    bool bHide=false;
    int counts=0;
    string param = "a";

};
