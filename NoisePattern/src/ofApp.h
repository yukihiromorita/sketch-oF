#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    float pattern(float );
    float pattern(float px, float py);
    float pattern(float px, float py,float pz);
    ofImage src;
    ofImage dist;
    
    int RGBtoHSB(int r,int g,int b);
    
    void pixelNoise(ofImage* src,ofImage* dst);
    
    void pixelNoise(ofImage* src,ofImage* dst,int ,int,int,int);
    
    float factor = 2.5;
};
