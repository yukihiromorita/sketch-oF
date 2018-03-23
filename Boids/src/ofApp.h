#pragma once

#include "ofMain.h"
#include "Boid.h"
#include "FlowField.h"
#include "Path.h"
#include "Flock.h"

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
    
        FlowField f;
        Path path;
//        Vehicle v = Vehicle(ofGetWidth()/2,ofGetHeight()/2);
        vector<Boid> boids ;
        vector< vector< vector<Boid> > > grid;
    
        vector< vector< vector<Boid> > > past;
        Flock flock;
        int cols,rows,resolution;
        int width,height;
};
