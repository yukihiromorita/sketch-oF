///aaaa

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i=0; i<255; i++) lightness.push_back({0});
    
    ofVec2f origin{0,0};
    
    src1.load("src1.jpg");
    src2.load("src2.jpg");
    width = src1.getWidth();
    height = src1.getHeight();
    pix1 = src1.getPixels();
    
    src2.resize(width, height);
    pix2 = src2.getPixels();
    
    //img1 put
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            pos.push_back(origin + ofVec2f(i,j));
            int index = i + j * width;
            int r = pix1[index*3 + 0];
            int g = pix1[index*3 + 1];
            int b = pix1[index*3 + 2];
            
            ofColor col = ofColor(r,g,b);
            imgCol1.push_back(col);
            int l = RGBtoL(r,g,b);
            lightness[l].push_back(col);
            lightPos1.push_back(origin + ofVec2f(l*2,lightness[l].size()-1));
        }
    }
    imgPos1 = pos;
    
    int h = 5;
    for(int i=0; i<255; i++) if(lightness[i].size() > h) h = lightness[i].size();
    
    for(int i=0; i<255; i++) lightness[i].clear();
    
    //img2 put
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            imgPos2.push_back(origin + ofVec2f(i,j));
            int index = i + j * width;
            int r = pix2[index*3 + 0];
            int g = pix2[index*3 + 1];
            int b = pix2[index*3 + 2];
            
            ofColor col = ofColor(r,g,b);
            imgCol2.push_back(col);
            int l = RGBtoL(r,g,b);
            lightness[l].push_back(col);
            lightPos2.push_back(origin + ofVec2f(l*2,lightness[l].size()-1));
        }
    }
    
    for(int i=0; i<255; i++) if(lightness[i].size() > h) h = lightness[i].size();
    
    ofBackground(255);
    ofSetWindowShape(MAX(255*2,width), h);
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
}

void ofApp::move(vector<ofVec2f> &prevPos, vector<ofVec2f> &nextPos,int index){
    if(prevPos.size() == nextPos.size()){
        vector<ofColor> c = index == 1 ? imgCol1 : index == 2 ? imgCol2 : imgCol1;
        //easing
        mesh.clear();
        for(int i=0; i<width*height; i++){
            prevPos[i] += (nextPos[i] - prevPos[i])/25.;
//            mesh.addColor(imgCol1[i]);
            mesh.addColor(c[i]);
            mesh.addVertex(ofVec3f(prevPos[i].x, prevPos[i].y, 0));
        }
        mesh.draw();
        //lerp
//        float time = 100;
//        static int count = 0;
//        for(int i=0; i<width*height; i++){
//            ofVec2f p = prevPos[i] + (nextPos[i] - prevPos[i]) / time * count;
//            ofSetColor(imgCol1[i]);
//            ofDrawCircle(p.x, p.y, 1);
//        }
//        static int diff = 1;
//        diff = count == time ? -1
//             : count == 0 ? 1
//             : diff;
//        count += diff;
        
    }else{
        ofLog() << "can't move";
    }
}

//--------------------------------------------------------------
void ofApp::update(){
//    ofSetWindowTitle(ofToString(ofGetFrameRate()));
//    ofSetWindowTitle(ofToString(mode));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    static int mode = 0;
    float threshold = 0.1;
    if(pos[0].distance(lightPos1[0]) < threshold){
        mode = 1;
    }
    if(pos[0].distance(lightPos2[0]) < threshold){
        mode = 2;
    }
    if(mode == 3 && pos[0].distance(imgPos1[0]) < threshold){
        mode = 0;
    }
    if(mode == 2 && pos[0].distance(imgPos2[0]) < threshold){
        mode = 3;
    }
    
    
    if(mode == 0)move(pos,lightPos1,1);
    else if(mode == 1) move(pos,lightPos2,2);
    else if(mode == 2) move(pos,imgPos2,2);
    else if(mode == 3) move(pos,imgPos1,1);
    
    ofSetWindowTitle(ofToString(mode));
    
}

float ofApp::RGBtoL(int r, int g, int b){
    int max = std::max({r,g,b});
    int min = std::min({r,g,b});
    
    return (max + min)/2;
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
