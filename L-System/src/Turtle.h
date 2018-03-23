//
//  Turtle.h
//  8_L-System
//
//  Created by Yukihiro Morita on 2017/12/30.
//
//

#ifndef Turtle_h
#define Turtle_h
#include "ofMain.h"

// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

class Turtle {
public:
    string todo;
    float len;
    float theta;
    float lineW;
    Turtle(){}
    Turtle(string s, float l, float t) {
        todo = s;
        len = l;
        theta = t;
        lineW = 2.;
    }
    
    void render() {
        ofSetColor(0, 175);
        ofSetLineWidth(lineW);
        for (int i = 0; i < todo.length(); i++) {
            char c = todo.at(i);
            if (c == 'F' || c == 'G') {
                ofDrawLine(0, 0, len, 0);
                ofTranslate(len, 0);
            } else if (c == '+') {
                ofRotate(theta);
            } else if (c == '-') {
                ofRotate(-theta);
            } else if (c == '[') {
                ofPushMatrix();
            } else if (c == ']') {
                ofPopMatrix();
            }
        }
    }
    
    void setLen(float l) {
        len = l;
    } 
    
    void changeLen(float percent) {
        len *= percent;
    }
    
    void setToDo(string s) {
        todo = s;
    }
};

#endif /* Turtle_h */
