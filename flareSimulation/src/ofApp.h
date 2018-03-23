#pragma once

#include "ofMain.h"
#include <random>
#include "ofxGui.h"
#include "ofxExportImageSequence.h"

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
    void generate();
    void distChanged(float &v);
    
    float count=0;
    
    ofxPanel gui;
    ofxFloatSlider maxHue;
    ofParameter<float> ave,sd;
    ofParameter<int> green,blue;
    ofxExportImageSequence seq_out;
    
};
