#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    resolution = 15;
    width = ofGetWidth();
    height = ofGetHeight();
    cols = width/resolution;     // Calculate cols & rows
    rows = height/resolution;
    
    cout << "gridNUM = " << rows * cols << endl;
    
    past.resize(cols);
    for(int i=0; i<cols; i++){
        past[i].resize(rows);
    }
    
    grid.resize(cols);
    for(int i=0; i<cols; i++){
        grid[i].resize(rows);
    }
    
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            for(int k=0 ; k<1; k++){
                past[i][j].push_back(Boid(ofRandom(width),ofRandom(height)));
            }
        }
    }
    
//    past = vector<vector<vector<Boid>>>(cols, vector<vector<Boid>>(rows, vector<Boid>(5, Boid(ofRandom(ofGetWidth()),ofRandom(ofGetHeight())) )));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle( ofToString(ofGetFrameRate()) );
    
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            grid[i][j].clear();
            grid[i][j].shrink_to_fit();
        }
    }
    
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            for (Boid& b : past[i][j]) {
                int x = b.position.x / resolution;
                int y = b.position.y / resolution;
                
                if (x >= 0 && x < cols && y >= 0 && y < rows) grid[x][y].push_back(b);
                else if(x == cols && y == rows){
                    grid[x-1][y-1].push_back(b);
                }else if(x == cols){
                    grid[x-1][y].push_back(b);
                }else if(y == rows){
                    grid[x][y-1].push_back(b);
                }else{
                    cout<<"x:"<< b.position.x<<" y:"<<b.position.y;
                    cout<<" x:"<<x<<" y:"<<y<<endl;
                }
                
            }
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            for (Boid& b : grid[i][j]) {
                b.flock(grid[i][j]);
                b.update();
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            for(Boid& b : grid[i][j])b.display();
        }
    }
    
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            past[i][j].clear();
            past[i][j].shrink_to_fit();
        }
    }
    
    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
//            past[i][j] = grid[i][j];
            
            copy(grid[i][j].begin(), grid[i][j].end(), back_inserter(past[i][j]) );
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
