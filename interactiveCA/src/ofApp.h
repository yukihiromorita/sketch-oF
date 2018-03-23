#pragma once

#include "ofMain.h"
#include "GOL.hpp"

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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    bool isMoved(int i,int j,unsigned char* vidpix,unsigned char* imgpix);
    
//    GOL gol = GOL(640,480);
//    GOL gol = GOL(480,360);
//    GOL gol = GOL(320,240);
    ofVideoGrabber video;
    ofImage bg;
    
    int wid = 720;
    int hei = wid /4 *3;
    
    GOL gol = GOL(wid,hei);
    int ruleB = 2;
    int ruleD = 100;
    
    int count = 0;
    int cntthre = wid * hei / 60;
    bool isMovedWhole = false;
    float thre = 10.0;
    
    unsigned char* p;
    unsigned char* _pix;
    ofFbo fbo;
    
    float scale = 1.5;
    ofImage* dist;
};

