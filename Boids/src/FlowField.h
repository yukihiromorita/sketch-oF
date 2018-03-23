#include "ofMain.h"

#ifndef FlowField_h
#define FlowField_h

using namespace std;

class FlowField{
public:
    
    int cols ;
    int rows ;
    vector< vector<ofVec2f> > field;
    int resolution;
    
    FlowField(){
        resolution = 10;
        cols = ofGetWidth() / resolution;
        rows = ofGetHeight() / resolution;
        field.resize(cols);
        for(int i=0; i<cols; i++){
            field[i].resize(rows);
        }
    }
    
    void init(){
        float xoff = 0;
        for(int i=0 ; i<cols; i++){
            float yoff = 0;
            for(int j=0 ; j<rows; j++){
                float theta = ofMap(ofNoise(xoff,yoff,ofGetElapsedTimef()),0,1,0,TWO_PI);
                field[i][j] = ofVec2f(cos(theta),sin(theta) );
                yoff += 0.1;
            }
            xoff += 0.1;
        }
    }
    
    void display() {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                drawVector(field[i][j],i*resolution,j*resolution,resolution-2);
            }
        }
    }
    
    
    
    void drawVector(ofVec2f v,float x,float y,float scayl){
        ofPushMatrix();
        float arrowsize = 4;
        // Translate to position to render vector
        ofTranslate(x,y);
//        stroke(0,100);
        ofSetColor(0,100);
        // Call vector heading function to get direction (note that pointing to the right is a heading of 0) and rotate
        float theta = ofRadToDeg(atan2(v.y, v.x)) + 90;
        ofRotate(theta);
        // Calculate length of vector & scale it to be bigger or smaller if necessary
        float len = v.length()*scayl;
        // Draw three lines to make an arrow (draw pointing up since we've rotate to the proper direction)
        ofDrawLine(0,0,len,0);
        ofDrawLine(len,0,len-arrowsize,+arrowsize/2);
        ofDrawLine(len,0,len-arrowsize,-arrowsize/2);
        ofPopMatrix();
    }
    
    ofVec2f lookup(ofVec2f lookup){
        int column = int(ofClamp(lookup.x / resolution, 0 ,cols-1));
        int row = int(ofClamp(lookup.y / resolution, 0 ,rows-1));
        return field[column][row] ;
    }
    
};

#endif /* FlowField_h */
