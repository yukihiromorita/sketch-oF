//
//  calc.h
//  
//
//  Created by Yukihiro Morita on 2016/05/16.
//
//
#include <stdio.h>
#include "ofMain.h"

class Calc{
public:
    Calc();
    
    void calcTornado();
    void init();
    
    ofVec3f bottom;
    float t;//parameter
    float h;//height
    float r;//radius
    float k;//constant
    float theta;
};