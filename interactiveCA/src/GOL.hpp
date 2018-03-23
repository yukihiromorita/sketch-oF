#ifndef GOL_hpp
#define GOL_hpp

#include <stdio.h>
#include "ofMain.h"
#endif /* GOL_hpp */
#include <vector>
using namespace std;

#define WIDTH 720
#define HEIGHT 540

class GOL {
public:
    int columns;
    int rows;
    int board[WIDTH][HEIGHT];
    
    int col,row;
    std::vector< std::vector<int> > vboard;
    
    GOL(int _width,int _height);
    ~GOL();
    
    void init();
    void generate(int a, int b,int c,int d);
    void display(unsigned char* vidpix,ofImage* dist);
    
    void setBoard(int i, int j, int value) {
        //board[i][j] = value;
    }
    
    bool bVec = false;
};
