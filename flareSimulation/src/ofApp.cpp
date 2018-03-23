#include "ofApp.h"
//gui

int gridWidth = 1,gridHeight = 1;
const int gridNumX = 500,gridNumY = 200;
int gridNum = gridNumX * gridNumY;
int grid[gridNumX][gridNumY];

using my_engine = mt19937;
using my_distribution = normal_distribution<>;
my_engine mEngine{};
my_distribution mDistribution{55.0,15.0};

auto generate_random = bind(mDistribution,mEngine);


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowShape(gridWidth*gridNumX, gridHeight*gridNumY);
	
	gui.setup();
    ave.addListener(this, &ofApp::distChanged);
    sd.addListener(this, &ofApp::distChanged);
	gui.add(maxHue.setup("maxHue", 150, 100, 255));
    gui.add(ave.set("Average", 50, 0, 100));
    gui.add(sd.set("SD", 15, 0, 100));
//    gui.add(green.set("green", 0, 0, 255));
//    gui.add(blue.set("blue", 0, 0, 255));
    
    seq_out.setup(gridWidth*gridNumX, gridHeight*gridNumY, 30);
    seq_out.startExport();
    
//    generate();
    
}

void ofApp::generate(){
//	for(auto& g:grid){
//		g[0] = ofRandom(30,70);
//		g[0] = round(generate_random());
//	}
	
	for(int i=0; i<gridNumX; i++){
		grid[i][0] = round(generate_random());
//        grid[i][0] = ofRandom(30,70);
//        grid[i][0] = 100*ofNoise(count*0.01+i*0.01+0.01*generate_random());
        
	}
	
	for(int i=0; i<gridNumX; i++){
		if(i == 0 )				  grid[i][1] = round((grid[i][0] + grid[gridNumX-1][0] +grid[i+1][0])/3);
		else if(i == gridNumX-1 ) grid[i][1] = round((grid[i][0] + grid[i-1][0] +grid[0][0])/3);
		else					  grid[i][1] = ceil((grid[i][0] + grid[i-1][0] +grid[i+1][0])/3)+ofRandom(-1,1);
	}
	for(int j=2; j<gridNumY; j++){
        for(int i=0; i<gridNumX; i++){
			if(i == 0 )				  grid[i][j] = round((grid[i][j-1] + grid[gridNumX-1][j-1] +grid[i+1][j-1] + grid[i][j-2])/4);
			else if(i == gridNumX-1 ) grid[i][j] = round((grid[i][j-1] + grid[i-1][j-1]		  +grid[0][j-1]	  + grid[i][j-2])/4);
			else				      grid[i][j] = ceil((grid[i][j-1] + grid[i-1][j-1]		  +grid[i+1][j-1] + grid[i][j-2])/4)+ofRandom(-1,1);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
	
	static float c = 0.01;
	if(count >0.01*60*10) c = -0.01;
	else if(count < 0) c = 0.01;
//	else	c = 0.01;
	count += c;
	
	generate();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    seq_out.begin();
//    ofClear(0);
    
	for(int i=0; i<gridNumX; i++){
		for(int j=0; j<gridNumY; j++){
			ofSetColor(ofColor::fromHsb(ofClamp(ofMap(grid[i][j],0,80,0,maxHue),0,maxHue),255,255));
//            ofSetColor(ofClamp(ofMap(grid[i][j],0,100,0,maxHue),0,maxHue),green,blue);
			ofDrawRectangle(gridWidth*i, ofGetHeight()-gridHeight*(j+1), gridWidth, gridHeight);
//            ofDrawBitmapString(grid[i][j], 20+gridWidth*i, 50+gridHeight*j);
		}
	}
    
//    seq_out.end();
    
//    ofSetColor(255);
//    seq_out.draw(0 ,0);
    
	gui.draw();
}

void ofApp::distChanged(float &v){
    mDistribution = my_distribution{ave,sd};
    generate_random = bind(mDistribution,mEngine);
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
