//
//  CellSystem.h
//  CA2
//
//  Created by Yukihiro Morita on 2017/12/27.
//
//

#ifndef CellSystem_h
#define CellSystem_h
#include "Cell.h"
#include "ofMain.h"

class CellSystem{
public:
    int col,row;
    vector<vector<Cell>> cells;
    vector<vector<Cell>> next;
    
    CellSystem(int _col,int _row){
        col = _col;
        row = _row;
        
        for(int i=0; i<col; i++){
            vector<Cell> c;
            cells.push_back(c);
            next.push_back(c);
            for(int j=0; j<row; j++){
                cells[i].push_back(Cell());
                next[i].push_back(Cell());
            }
        }
//        next = cells;
        
//        for(int i=0; i<col; i++){
//            vector<Cell> c;
//            next.push_back(c);
//            for(int j=0; j<row; j++){
//                cells[i].push_back(Cell());
//            }
//        }
    }
    
    inline void update(){
            for(int x=1; x<col-1; x++){
                for(int y=1; y<row-1; y++){
                    int neighbor = 0;
        
                    if(x % 2 == 0){
                        for(int i=-1; i<=1; i++){
                            for(int j=0; j<=1; j++) {
                                neighbor += cells[x+i][y+j].state;
                            }
                        }
                        neighbor += cells[x][y-1].state;
                        neighbor -= cells[x][y].state;
                    }else{
                        for(int i=-1; i<=1; i++){
                            for(int j=-1; j<=0; j++) {
                                neighbor += cells[x+i][y+j].state;
                            }
                        }
                        neighbor += cells[x][y+1].state;
                        neighbor -= cells[x][y].state;
                    }
        
                    if     (cells[x][y].state == 1 && neighbor <  2) next[x][y].state = 0;
                    else if(cells[x][y].state == 1 && neighbor >  3) next[x][y].state = 0;//0,1,4~6は死ぬ
                    else if(cells[x][y].state == 0 && neighbor == 2) next[x][y].state = 1;//3以上で生き返る
                    else if(cells[x][y].state == 0 && neighbor == 3) next[x][y].state = 1;//3以上で生き返る
                    else    next[x][y].state = cells[x][y].state;
                }
            }
    }
    
    inline void draw(){
        for(int i=0; i<col; i++){
            for(int j=0; j<row; j++){
                cells[i][j].draw(i,j);
            }
        }
    }
    
    inline void succeed(){
        for(int i=0; i<col; i++){
            for(int j=0; j<row; j++){
                cells[i][j].state = next[i][j].state;
            }
        }
    }
};

#endif /* CellSystem_h */
