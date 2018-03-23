#pragma once
#include "ofMain.h"

class Line {
public:
    int typ,pos;
    int from,to;
    
    Line(int t,int p);
    bool check(vector<Line> lines,int margin);
    void draw();
    void print();

};