#include "ofApp.h"
int dx;

static vector<ofVec3f> featureDetect(ofPixels& src)
{
    cv::Mat srcMat = toCv(src);
    
    cv::Mat descriptors;
    vector<cv::KeyPoint> keyPoints;
    
    cv::Ptr<cv::AKAZE> detector = cv::AKAZE::create();
    
    vector<ofVec3f> vec;
    
    detector->detectAndCompute(srcMat, cv::noArray(), keyPoints, descriptors);
    
    //    for( vector<cv::KeyPoint>::iterator itk = keyPoints.begin();
    //        itk != keyPoints.end();
    //        ++itk)
    //    {
    //        vec.push_back(toOf(itk->pt));
    //    }
    
    for(auto k : keyPoints){
        vec.push_back(toOf(k.pt));
    }
    return vec;
}


//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(200);
    ofEnableSmoothing();
    ofSetCircleResolution(128);
    
    dx = 6;
    x_thre = 10;
    
//    dir.allowExt("jpg");
    dir.listDir("");
    loadImage("n");
    loadImage("p");
    ofSetWindowShape(img.getWidth(), img.getHeight()); //debug
    
    //voronoi setup
    bounds.set(0,0, ofGetWidth(), ofGetHeight());
    voronoi.setup(bounds);
    
    pts = featureDetect(img.getPixels());
    
    bImg = true;
    bDot = false;//fade in
    bLine = true;
    
    lineAlpha=255;
    dotAlpha=255;
    
    //gui setting
    gui.setup();
    gui.add(imgToggle.setup("image",true));
//    gui.add(img2Toggle.setup("image2",false));
    gui.add(delToggle.setup("delaunay",false));
    gui.add(voroToggle.setup("Voronoi",true));
    gui.add(dotToggle.setup("Feature Point",true));
    gui.add(dxSlider.setup("point num",20,1,200 ));
    gui.add(dx_max.setup("Max point num",30,10,200));
    gui.add(scanSpeed.setup("scan speed",(float)ofGetWidth()/(60*4),0.001,20));//6秒
    gui.add(radius.setup("point radius",5,0.3,10));
    gui.add(lineWidth.setup("line width",1.0,0.01,8.0));
    gui.add(imgAlpha.setup("image alpha",255,0,255));
    gui.add(lineShow.setup("line show",true));
    
//    gui.add(lineColor.setup("Line Color",ofColor::gray,ofColor(0,0,0,0),ofColor(255,255,255,255)));
//    lineColor.minimize();
    gui.add(delColor.setup("Delaunay Color",ofColor::lightGreen,ofColor(0,0,0,0),ofColor(255,255,255,255)));
    delColor.minimize();
    gui.add(vorColor.setup("Voronoi Color",ofColor::white,ofColor(0,0,0,0),ofColor(255,255,255,255)));
    vorColor.minimize();
    gui.add(dotColor.setup("Point Color",ofColor::red,ofColor(0,0,0,0),ofColor(255,255,255,255)));
    dotColor.minimize();
    
//    gui.add(sine.setup("sine",true));
//    gui.add(saw.setup("saw",false));
//    gui.add(square.setup("square",false));
//    gui.add(triangle.setup("triangle",false));
    guiShow = true;
    
    
    imageChanged();
    
    //sound setting
//    sound.load("sound/sine_750.wav");
//    sound.setLoop(true);
//    sound.setVolume(0.2);
//    sound.play();
    
    //img2 setting
//    img2.load("otherImg/branch1.png");
//    img2.resize(1920/2, 1080);
    
    
}

//--------------------------------------------------------------
void ofApp::update() {
//    ofSetWindowShape(img.getWidth(), img.getHeight());//debug
    ofSetLineWidth(lineWidth);
    
    voronoi.clear();
    for(int i=0; i<pts.size(); i += dxSlider ) {
        if (pts[i].x < x_thre) {
            voronoi.addPoint(pts[i]);
        }
    }
    voronoi.generateVoronoi();
    
    //delaunay
    if(delToggle){
        delaunay.reset();
        if (pts.size() > 15) {
            for (int i = 0; i < pts.size(); i += dxSlider) {
                if (pts[i].x < x_thre) {
                    delaunay.addPoint(pts[i]);
                }
            }
            delaunay.triangulate();
        }
    }
    
    //特徴点抽出の細かさを変化
    if(x_thre == 0 && dxSlider < dx_max) {
        dxSlider = dxSlider + 2;//間隔
    }
    
    //画像・点・線のフェードイン
    {
        
        //    if(bImg){
        //        if(imgAlpha<=255) imgAlpha += 5;
        //    }else{
        //        if(imgAlpha>=50) imgAlpha -= 5;
        //    }
        
        if(dotToggle && bDot) {
            dotAlpha += 0.5;
            if(x_thre == 0 ) dotAlpha = 10;
        }
        if(voroToggle && bLine) {
//            lineAlpha += 0.5;
                        lineAlpha += 2 ;
            if(x_thre == 0) lineAlpha = 10;
        }
    }
    
    x_thre += scanSpeed;
    if (x_thre > ofGetWidth()) x_thre = 0;
    
    stringstream ss;
//    ss<<"dx= "<<dx<<" Framerate= "<<ofGetFrameRate()<<" mode= "<<mode;
    ss<<" Framerate= "<<ofGetFrameRate();
    ofSetWindowTitle(ss.str() );
    
}

void ofApp::draw() {
    ofSetColor(255, imgAlpha);
    if(imgToggle)img.draw(0, 0);
//    if(img2Toggle)img2.draw(1920/2,0);
    
    //delaunay描画
    if(delToggle){
        if (bLine){
            ofPushStyle();
            ofNoFill();
            ofSetColor(delColor, lineAlpha);
            if(bLine)delaunay.draw();
            ofPopStyle();
        }
    }
    
    //voronoi描画
    ofPushStyle();
    ofSetColor(vorColor,lineAlpha);//debug
    if(voroToggle)voronoi.draw();
    ofPopStyle();
    
    //特徴点描画
    for (int i = 0; i < pts.size(); i+=dxSlider) {
        if (pts[i].x < x_thre) {
            ofPushStyle();
            ofSetColor(dotColor,dotAlpha);
            if(dotToggle)ofDrawCircle(pts[i].x, pts[i].y, radius);
            ofPopStyle();
        }
    }
    
    if(guiShow)gui.draw();
    
    ofSetColor(ofColor::blue);
    if(lineShow)ofDrawLine(x_thre, 0, x_thre, ofGetHeight());
    

    if(guiShow)ofDrawBitmapStringHighlight("g : GUI \nn : next\np : prev\ns : save", 20, 600);
}

void ofApp::loadImage(const string& tmp){
    static int file_index = 0;
    if(tmp == "n"){//next
        if(file_index < dir.getFiles().size()-1 )file_index++;
        else file_index = 0;
    }else if(tmp == "p"){//prev
        if(file_index > 0)file_index --;
        else file_index = dir.getFiles().size()-1;
    }
    img.load(dir.getPath(file_index));
//    img.resize(1920,1080);
    mode = file_index;
    imageChanged();
    
}

void ofApp::imageChanged(){//mode更新の後に呼ぶ
    pts.clear();
    delaunay.reset();
    voronoi.clear();
    pts = featureDetect(img.getPixels());
    ofSetWindowShape(img.getWidth(), img.getHeight());
//    bounds.set(0,0,ofGetWidth(),ofGetHeight());
//    voronoi.setup(bounds);
    
    /*
    switch(mode){
        case 0 :
            lineColor = ofColor(45);
            dotColor = ofColor(249,58,53,255);
            dxSlider = 5;//initial
            dx_max = 25;
            radius = 4.5;
            lineWidth = 0.7;
            break;
        case 1 :
            lineColor = ofColor(35,35,35);
            dotColor = ofColor(249,58,53);
            dxSlider = 5;
            dx_max = 25;
            radius = 4;
            lineWidth = 1.0;
            break;
        case 2 :
            lineColor = ofColor(188,188,188);
            dotColor = ofColor(219,43,33);
            dxSlider = 5;
            dx_max = 30;
            radius = 4;
            lineWidth = 0.7;
            break;
        case 3 :
            lineColor = ofColor(101,175,175);
            dotColor = ofColor(255,127,0);
            dxSlider = 7;
            dx_max = 35;
            radius = 4;
            lineWidth = 1.6;
            break;
        case 4 :
            lineColor = ofColor(223,223,223);
            dotColor = ofColor(41,96,240);
            dxSlider = 5;
            dx_max = 25;
            radius = 4.8;
            lineWidth = 1.0;
            break;
        case 5 :
            lineColor = ofColor(190,190,190);
            dotColor = ofColor(37,37,37);
            dxSlider = 5;
            dx_max = 25;
            radius = 4.8;
            lineWidth = 1.0;
            break;
        case 6 :
            lineColor = ofColor(206,206,206);
            dotColor = ofColor(236,122,193);
            dxSlider = 2;
            dx_max = 20;
            radius = 4.5;
            lineWidth = 1.0;
            break;
        case 7 :
            lineColor = ofColor(35,35,35);
            dotColor = ofColor(249,58,53);
            dxSlider = 5;
            dx_max = 25;
            radius = 4;
            break;
        case 8 :
            lineColor = ofColor(50,54,130);
            dotColor = ofColor(19,15,15);
            dxSlider = 5;
            dx_max = 25;
            radius = 4;
            lineWidth = 2.0;
            imgAlpha = 150;
            break;
        case 9 :
            lineColor = ofColor(222,222,222);
            dotColor = ofColor(206,206,206);
            dxSlider = 10;
            dx_max = 25;
            radius = 4;
            lineWidth = 2.0;
            imgAlpha = 150;
            break;
    }
    */
//    sound.stop();
//    sound.play();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 's':
            ofSaveScreen(ofGetTimestampString() + ".png");
            break;
        case 'g' : guiShow = !guiShow; break;
        case 'n':
            loadImage("n");
            break;
        case 'p':
            loadImage("p");
            break;
        case 'd' : bDot = !bDot;
            break;
        case 'l' : bLine = !bLine;
            break;
        case 'I' : bImg = !bImg;
            break;
//        case 'z' : dxSlider = 5; break;
        case 'D' : pts = featureDetect(img.getPixels()); break;
//        case 'f' : {
//            ofToggleFullscreen();
//            img.resize(ofGetWidth(),ofGetHeight() );
////            bounds.set(0,0,ofGetWidth(),ofGetHeight());
////            voronoi.setup(bounds);
//            break;
//        }
        case 'L' : lineShow = !lineShow; break;
//        case 'm' :
//            if(sine) sound.load("sound/sine_750.wav");
//            if(saw) sound.load("sound/sawtooth_1050.wav");
//            if(square) sound.load("sound/square_550.wav");
//            if(triangle) sound.load("sound/triangle_800.wav");
//            sound.setVolume(0.2);
//            sound.play();
//            break;
//        case ' ' :
//            img.resize(1920/2, 1080);
//            pts = featureDetect(img.getPixels());
//            break;
//        case 'P' :
//            img2.load("otherImg/pyramid.jpg");
//            img2.resize(1920/2,1080);
//            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    bounds.set(0,0,w,h);
    voronoi.setup(bounds);
    pts = featureDetect(img.getPixels());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
