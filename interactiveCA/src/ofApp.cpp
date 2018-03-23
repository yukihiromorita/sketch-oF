#include "ofApp.h"
//fboでリサイズ

//--------------------------------------------------------------
void ofApp::setup(){
    //    ofSetFrameRate(30);
    ofSetWindowShape(wid*scale,hei*scale);
    
//        video.initGrabber(wid, hei);
    video.initGrabber(720, 540);
    //    video.initGrabber(1080, 810);
//    video.setDesiredFrameRate(30);
    
    
    bg.allocate(wid,hei,OF_IMAGE_COLOR);
    p = bg.getPixels().getData();
    _pix = bg.getPixels().getData();
    fbo.allocate(wid,hei,GL_RGB);
//    fbo.allocate(480,360,GL_RGB);
    
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofDisableAlphaBlending();
//    ofSetBackgroundAuto(false);
    
    
    dist = new ofImage;
    dist->allocate(wid,hei,OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    dist->update();
    video.update();
    
    if (video.isFrameNew()){
        count = 0;
        fbo.begin();
        ofClear(255);
        video.draw(0, 0, fbo.getWidth(), fbo.getHeight());
        fbo.end();
        
        dist->clear();
        
        ofPixels pix;
        fbo.readToPixels(pix);
        p = pix.getData();
        
        _pix = bg.getPixels().getData();
        
        for (int i=0; i<wid; i++) {
            for (int j=0; j<hei; j++) {
                if (isMoved(i, j,p,_pix)) {
                    //                    gol.vboard[i][j] = 1;
                    gol.board[i][j] = 1;
                    count++;
                }//else gol.board[i][j] = 0;
            }
        }
        
        bg.setFromPixels(pix);
        
        //        isMovedWhole = count > cntthre ? true : false;
        
        if (count < cntthre) {//止まったら = CA活発
            ruleB = 4;
            ruleD = 4;
        } else {//動いたら = CA消極
            ruleB = 2;
            ruleD = 7;
        }
        
        gol.generate(2, ruleB, 3, ruleD);
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (video.isFrameNew()) {
        gol.display(p,dist);
    }
    
    ofScale(-scale,scale);
    dist->draw(-wid,0);
    //    dist->draw(0,0);
}

inline bool ofApp::isMoved(int i, int j,unsigned char* vidpix,unsigned char* imgpix) {//
    int index = i + j * wid;
    
    int diff_red   = abs(vidpix[index*3  ] - imgpix[index*3  ]);
    int diff_green = abs(vidpix[index*3+1] - imgpix[index*3+1]);
    int diff_blue  = abs(vidpix[index*3+2] - imgpix[index*3+2]);
    
    if (diff_red > thre && diff_green > thre && diff_blue > thre) return true;
    else return false;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        thre += 1.0;
        cout<<thre;
    } else if (key == '2') {
        thre -= 1.0;
        cout<<thre;
    } else if (key == '!') {
        thre += 5.0;
        cout<<thre;
    } else if (key == '"') {
        thre -= 5.0;
        cout<<thre;
    } else if (key == '-') {
        cntthre -= 100;
        cout<< "cnt thre= " << cntthre <<endl;
    } else if (key == '+') {
        cntthre += 100;
        cout << "cnt thre= " << cntthre <<endl;
    }
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
