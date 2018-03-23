//TODO:dxの初めをプリセットに追加
//渋谷
#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxVoronoi.h"
#include "ofxGui.h"
#include "utils.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/photo.hpp>


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
		
    
    void loadImage(const string&);
    void imageChanged();
    vector<ofVec3f> pts;
    ofImage img,img2;
    ofxDelaunay delaunay;
    float x_thre;
    ofDirectory dir;
    
    bool bImg,bDot,bLine;
    float dotAlpha,lineAlpha;
    
    ofColor dotCol=ofColor::orange;
    ofColor lineCol=ofColor::gray;
    
    
    int mode;
    
    ofxVoronoi voronoi;
    ofRectangle bounds;
    
    ofxPanel gui;
    ofxToggle delToggle,voroToggle,dotToggle;
    ofxIntSlider dxSlider,dx_max,pointAdd;
    ofxColorSlider lineColor,dotColor,delColor,vorColor;
    ofxFloatSlider scanSpeed;
    ofxFloatSlider radius;
    ofxFloatSlider lineWidth;
    ofxFloatSlider imgAlpha;
    bool guiShow;
    
    ofSoundPlayer sound;
    ofxToggle sine,saw,square,triangle,lineShow;
    
    ofxToggle imgToggle,img2Toggle;
};
