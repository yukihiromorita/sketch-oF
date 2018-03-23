#include "ofApp.h"
int counter = 0;
//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetFrameRate(15);
    ofSetBackgroundAuto(false);
    
    vector<Rule> ruleset;
    ruleset.push_back( Rule('F', "FF+[+F-F-F]-[-F+F+F]") );
//    ruleset.push_back( Rule('F', "FF+[+F-F]-[-F+F]") );
    lsys = LSystem("F", ruleset);
    turtle = Turtle(lsys.getSentence(), ofGetHeight()/5, 40 );
    
    
    ofBackground(255);
    ofSetColor(0);
    ofTranslate(ofGetWidth()/2, ofGetHeight());
    ofRotate(-90);
    turtle.render();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(255);
//    ofSetColor(0);
//    //text("Click mouse to generate", 10, height-10);
//    
//    ofTranslate(ofGetWidth()/2, ofGetHeight());
//    ofRotate(-90);
//    turtle.render();
//    noLoop();
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
    if (counter < 10) {
        ofPushMatrix();
        lsys.generate();
//        cout << (lsys.getSentence()) << endl;
        turtle.setToDo(lsys.getSentence());
        turtle.changeLen(0.5);
        ofPopMatrix();
        
        ofBackground(255);
        ofSetColor(0);
        ofTranslate(ofGetWidth()/2, ofGetHeight());
        ofRotate(-90);
        turtle.lineW *= 0.8;
        turtle.render();
        
        counter++;
        ofLog() << "counter:"<<counter;
    }
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
