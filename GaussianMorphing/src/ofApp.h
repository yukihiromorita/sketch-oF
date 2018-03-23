//mo

#pragma once

#include "ofMain.h"

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
		
    ofImage src1,src2;
    ofPixels pix1,pix2;
    int width,height;
    vector<ofVec2f> pos;
    vector<ofVec2f> imgPos1,imgPos2;
    vector<ofVec2f> lightPos1,lightPos2;
    vector<ofColor> imgCol1,imgCol2;
    
    ofVboMesh mesh;
    
    float RGBtoL(int r, int g, int b);
    vector< vector<ofColor> > lightness;
    
    void move(vector<ofVec2f> &prevPos, vector<ofVec2f> &nextPos,int index);
};
