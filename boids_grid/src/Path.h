#ifndef Path_h
#define Path_h
#include "ofMain.h"

class Path{
public:
//    ofVec2f start,end;
    float radius;
    vector<ofVec2f> points;
    
    Path(){
        radius = 20;
//        start = ofVec2f(0,ofGetHeight()/3);
//        start = ofVec2f(ofGetWidth(),2*ofGetHeight()/3);
    }
    
    void addPoint(float x, float y){
        ofVec2f point(x,y);
        points.push_back(point);
    }
    void newPath(){
        points.clear();
        addPoint(-20, ofGetHeight()/2);
        addPoint(ofRandom(0, ofGetWidth()/2), ofRandom(0, ofGetHeight()));
        addPoint(ofRandom(ofGetWidth()/2, ofGetWidth()), ofRandom(0, ofGetHeight()));
        addPoint(ofGetWidth()+20, ofGetHeight()/2);
    }
    
    void display(){
        ofPushStyle();
        //        ofSetColor(0,100);
        //        ofSetLineWidth(radius * 2);
        //        ofDrawLine(start.x,start.y,end.x,end.y);
        //
        //        ofSetColor(0);
        //        ofSetLineWidth(1);
        //        ofDrawLine(start.x,start.y,end.x,end.y);
        
        // Draw thick line for radius
        ofSetColor(175);
        ofSetLineWidth(radius*2);
        ofNoFill();
        ofBeginShape();
        for (ofVec2f v : points) {
            ofVertex(v.x, v.y);
        }
        ofEndShape();
        // Draw thin line for center of path
        ofSetColor(0);
        ofSetLineWidth(1);
        ofNoFill();
        ofBeginShape();
        for (ofVec2f v : points) {
            ofVertex(v.x, v.y);
        }
        ofEndShape();
        ofPopStyle();
    }
    
};

#endif /* Path_h */
