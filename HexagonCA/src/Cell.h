//
//  Cell.h
//  CA2
//
//  Created by Yukihiro Morita on 2017/12/22.
//
//

#ifndef Cell_h
#define Cell_h
#include "ofMain.h"
#define SQRT3 1.73205080756887729352744634150587236694280525

class Cell{
public:
    float r;
    int x,y;
    float state;
    
    Cell(){
        r = 6;
        state = (int)ofRandom(2);
    };
    Cell(float _r){
        r = _r;
    };
    
    void init(){
        
    }
    
    inline void drawHexagon(int _x, int _y){
        ofPushStyle();
        ofSetLineWidth(1);
        if(state == 1) ofSetColor(32);
//        else ofSetColor(255);
//        ofSetColor(32);
//        ofNoFill();
        
        ofSetPolyMode(OF_POLY_WINDING_NONZERO);
        ofPushMatrix();
        ofTranslate(_x,_y);
        ofBeginShape();
        ofVertex(r, 0);
        ofVertex(r/2 , r * SQRT3/2 );
        ofVertex(-r/2, r * SQRT3/2 );
        ofVertex(-r, 0);
        ofVertex(-r/2, -r * SQRT3/2 );
        ofVertex(r/2 , -r * SQRT3/2 );
        ofEndShape();
        ofPopMatrix();
        ofPopStyle();
    }
    
    void draw(int i,int j){
        
        if(i % 2 == 0 ){//even
            drawHexagon(r + 3*r*i/2, r * SQRT3 / 2 + j * r * SQRT3);
        }else{ //odd
            //      drawHexagon(2*r*3/2 * i /2, SQRT3 * r * j); //weird
            drawHexagon(r + r*3/2*i, SQRT3 * r * j); //right
        }
    }
    
    void update(){
        
    }
};

#endif /* Cell_h */
