#include "GOL.hpp"

GOL::GOL(int _width,int _height){
    
    columns = WIDTH;
    rows = HEIGHT;
    
    col = _width;
    row = _height;
    if(bVec){
        vboard.resize(_width);
        for( int i=0; i < _width; i++ ){
            vboard[i].resize(_height);
        }
    }
    
    init();
    
}

GOL::~GOL(){
    cout<<"deconstructor"<<endl;
}

void GOL::init() {
    
    for (int i = 1; i < columns-1; i++) {
        for (int j = 1; j < rows-1; j++) {
            board[i][j] = int(ofRandom(2));
            
        }
    }
    
    if(bVec){
        for (int i = 1; i < col-1; i++) {
            for (int j = 1; j < row-1; j++) {
                vboard[i][j] = int(ofRandom(2));
            }
        }
    }
}


void GOL::generate(int a, int b, int c, int d ) {
    int next[WIDTH][HEIGHT];
    for (int x = 1; x < columns-1; x++) {
        for (int y = 1; y < rows-1; y++) {
            
            int neighbors = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    neighbors += board[x+i][y+j];
                }
            }
            
            neighbors -= board[x][y];
            
            if      ((board[x][y] == 1) && (neighbors <  a)) next[x][y] = 0;           // 生で1以下なら死ぬ
            else if ((board[x][y] == 1) && (neighbors >  b)) next[x][y] = 0;           // 生で4以上なら死ぬ
            else if ((board[x][y] == 0) && (neighbors == c)) next[x][y] = 1;           // 死で3なら生き返る
            else if ((board[x][y] == 0) && (neighbors == d)) next[x][y] = 1;           // 死で3なら生き返る
            else                                             next[x][y] = board[x][y];  // Stasis
            
        }
    }
    
    for(int i=0;i<columns;i++){
        for(int j=0; j<rows; j++){
            board[i][j] = next[i][j];
        }
    }
    
    if(bVec){
        vector< vector<int> > vnext;
        vnext.resize(col);
        for( int i=0; i<col; i++ ){
            vnext[i].resize(row);
        }
        
        for (int x = 1; x < col-1; x++) {
            for (int y = 1; y < row-1; y++) {
                
                int neighbors = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        neighbors += vboard[x+i][y+j];
                    }
                }
                
                neighbors -= vboard[x][y];
                
                if      ((vboard[x][y] == 1) && (neighbors <  a)) vnext[x][y] = 0;
                else if ((vboard[x][y] == 1) && (neighbors >  b)) vnext[x][y] = 0;
                else if ((vboard[x][y] == 0) && (neighbors == c)) vnext[x][y] = 1;
                else if ((vboard[x][y] == 0) && (neighbors == d)) vnext[x][y] = 1;
                else                                              vnext[x][y] = vboard[x][y];
                
            }
        }
        for(int i=0;i<col;i++){
            for(int j=0; j<row; j++){
                vboard[i][j] = vnext[i][j];
            }
        }
    }
}

void GOL::display(unsigned char* vidpix,ofImage* dist) {
    unsigned char px[WIDTH*HEIGHT*3];
    
    for ( int i = 0; i < columns; i++) {
        for ( int j = 0; j < rows; j++) {
            int index = i + j * columns;
            static int lastLive;
            
            if (board[i][j] == 1) {
                px[index*3  ] = vidpix[index*3  ];
                px[index*3+1] = vidpix[index*3+1];
                px[index*3+2] = vidpix[index*3+2];
                
                lastLive = index;
            }else{
                px[index*3  ] = 0;
                px[index*3+1] = 0;
                px[index*3+2] = 0;
                
                px[index*3  ] = vidpix[lastLive*3  ];
                px[index*3+1] = vidpix[lastLive*3+1];
                px[index*3+2] = vidpix[lastLive*3+2];
            }
            
        }
    }
    
    if(bVec){
        unsigned char *p;
        p = new unsigned char[col * row * 3];
        for ( int i = 0; i < col; i++) {
            for ( int j = 0; j < row; j++) {
                int index = i + j * col;
                
                if (vboard[i][j] == 1) {
                    //                    p[index*3  ] = vidpix[index*3  ];
                    //                    p[index*3+1] = vidpix[index*3+1];
                    //                    p[index*3+2] = vidpix[index*3+2];
                    //                }else{
                    //                    p[index*3  ] = 0;
                    //                    p[index*3+1] = 0;
                    //                    p[index*3+2] = 0;
                }
            }
        }
        dist->setFromPixels(p, col, row, OF_IMAGE_COLOR);
        delete[] p;
    }
    
    dist->setFromPixels(px, columns, rows, OF_IMAGE_COLOR);
    dist->update();
    
    
}
