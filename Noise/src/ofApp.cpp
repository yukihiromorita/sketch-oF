//TODO:
//staticの謎
//pattern()外部ファイル化

#include "ofApp.h"

int ofApp::RGBtoHSB(int r,int g, int b){
    
    float Max = max( {r,g,b} );
    float Min = min( {r,g,b} );
    int V = Max;
    int S,H;
    
    if(Max == 0 || Max == Min){
        S = 0;
        H = 0;
    }else{
        S = 255 * (Max - Min) / Max ;
        
        if(Max != Min){
            if(Max == r) H = 60 * (b - g)/(Max - Min);
            else if(Max == g) H = 60 * ( 2 + (r - b)/(Max - Min) ) ;
            else if(Max == b) H = 60 * ( 4 + (g - r)/(Max - Min) );
        }
    }
    return H;
}

void ofApp::pixelNoise(ofImage* src,ofImage* dst,int x1,int y1, int x2,int y2){
    
    //    ofPixels pix = src->getPixels();
    unsigned char* pix = src->getPixels().getData();
    
    static float count = 0;
    
    float rdiff,gdiff,bdiff;
    
    for(int y=y1; y<y2; y++){
        for(int x=x1; x<x2; x++){
            int index = y * src->getWidth() + x;
            
//            float H = 0.01 * RGBtoHSB(pix[index * 3],pix[index * 3 + 1],pix[index * 3 + 2]);
            
//            rdiff = gdiff = bdiff = 2 * ofNoise(0.01*x, 0.01*y, H) - 5;
            //            rdiff = gdiff = bdiff = 2 * ofNoise(0.01*x, 0.01*y) - 5;
//                        rdiff = gdiff = bdiff = 2 * pattern(0.01*(float)x, 0.01*(float)y, (float)H) - 5;
//            rdiff = ofMap(pattern(x*0.01,y*0.01,pix[index * 3  ]*0.1),0,1,100,200);
//            gdiff = ofMap(pattern(x*0.02,y*0.01,pix[index * 3+1]*0.1),0,1,100,200);
//            bdiff = ofMap(pattern(x*0.01,y*0.03,pix[index * 3+2]*0.1),0,1,100,200);

//            rdiff = ofMap(pattern(pix[index * 3  ]*0.01,count),0,1,100,200);
//            gdiff = ofMap(pattern(pix[index * 3+1]*0.2,count),0,1,100,200);
//            bdiff = ofMap(pattern(pix[index * 3+2]*0.05,count),0,1,100,200);
            
            rdiff   = int(1.0*255*pattern(x*0.01,y*0.01,count));
            gdiff   = int(1.0*255*pattern(x*0.01,y*0.01,count));
            bdiff   = int(1.0*255*pattern(x*0.01,y*0.01,count));
            
            //            rdiff = gdiff = bdiff = 10 * ofNoise(H,count) - 5;
            //            rdiff = gdiff = bdiff = 10 * pattern(H,count) - 5;
            
//            pix[index * 3    ] += rdiff;
//            pix[index * 3 + 1] += gdiff;
//            pix[index * 3 + 2] += bdiff;
            
            pix[index * 3    ] = rdiff;
            pix[index * 3 + 1] = gdiff;
            pix[index * 3 + 2] = bdiff;
        }
    }
    
    //    dst->setFromPixels(pix);
    dst->setFromPixels(pix,src->getWidth(),src->getHeight(),src->getImageType());
    
    count += 0.01;
}

void ofApp::pixelNoise(ofImage* src,ofImage* dst){
    
    //    ofPixels pix = src->getPixels();
    unsigned char* pix = src->getPixels().getData();
//    int* pix = src->getPixels().getData();
    
    static float count;
    
    float rdiff,gdiff,bdiff;
    
    for(int y=0; y<src->getHeight(); y++){
        for(int x=0; x<src->getWidth(); x++){
            int index = y * src->getWidth() + x;
            
            float H = 0.001 * RGBtoHSB(pix[index * 3],pix[index * 3 + 1],pix[index * 3 + 2]);
            
//            rdiff = gdiff = bdiff = 10 * ofNoise(0.01*x, 0.01*y, H) - 5; //good
//            rdiff = gdiff = bdiff = 10 * ofNoise(0.01*x, 0.01*y) - 5;
            rdiff = gdiff = bdiff = factor * ( pattern(0.001*x, 0.001*y,H) - 0.5);
//            rdiff = 10 * ( pattern((float)x*0.01,(float)y*0.01,count) - 0.5 );
//            gdiff = 10 * ( pattern((float)x*0.02,(float)y*0.01,count) - 0.5 );
//            bdiff = 10 * ( pattern((float)x*0.01,(float)y*0.03,count) - 0.5 );
//            gdiff = rdiff + 3;
//            bdiff = rdiff - 3;
            //            rdiff = gdiff = bdiff = 10 * ofNoise(H,count) - 5;
            //            rdiff = gdiff = bdiff = 10 * pattern(H,count) - 5;
            
            pix[index * 3    ] += rdiff;
            pix[index * 3 + 1] += gdiff;
            pix[index * 3 + 2] += bdiff;
            
//            ofClamp(pix[index * 3    ],10,10);
//            ofClamp(pix[index * 3  + 1],0,10);
//            ofClamp(pix[index * 3  + 2],0,10);

            
        }
    }
    
    //    dst->setFromPixels(pix);
    dst->setFromPixels(pix,src->getWidth(),src->getHeight(),src->getImageType());
    
    count += 0.01;
    
}

float ofApp::pattern(float px){
    float q = ofNoise(px + 5.2);
    float r = ofNoise(px + 4.0*q +1.7);
    float s = ofNoise(px + 4.0*r);
    
    return s;
    
}

float ofApp::pattern(float px, float py){
    
    ofVec2f q = ofVec2f( ofNoise(px, px),
                        ofNoise(py + 5.2,py + 1.3));
    
    ofVec2f r = ofVec2f( ofNoise( px + 4.0*q + ofVec2f(1.7,9.2) ),
                        ofNoise( py + 4.0*q + ofVec2f(8.3,2.8) ) );
    
    return ofNoise( (px+4.0*r).x,(py+4.0*r).y ); //2nd
    
    //    ofVec2f s = ofVec2f( ofNoise( px + 4.0*q + 4.0*r + ofVec2f(6.6,3.8) ),
    //                         ofNoise( py + 4.0*q + 4.0*r + ofVec2f(2.3,6.3) ) );
    
    //    return ofNoise( (px+4.0*s).x,(py+4.0*s).y ); //3rd
    
}

float ofApp::pattern(float px, float py,float pz){//not 3 dimension strictly
//    
//    ofVec2f q = ofVec2f(ofNoise(px,px),
//                        ofNoise(py+5.2,py+1.3)
//                        );
//    
//    ofVec2f r = ofVec2f( ofNoise( px + 4.0*q + ofVec2f(1.7,9.2) ),
//                        ofNoise( py + 4.0*q + ofVec2f(8.3,2.8) )
//                        );
//    //    return ofNoise( (px+4.0*r).x,(py+4.0*r).y ,pz );//2
//    
//    ofVec2f s = ofVec2f( ofNoise( px + 4.0*q + 4.0*r + ofVec2f(6.6,3.8) ),
//                        ofNoise( py + 4.0*q + 4.0*r + ofVec2f(2.3,6.3) )
//                        );
//    return ofNoise( (px+4.0*s).x,(py+4.0*s).y ,pz );//consider time
    
    float noisex =  px + 4.0 * ofNoise( px + 0.0, py + 0.0 , pz) ;
    float noisey =  py + 4.0 * ofNoise( px + 5.2, py + 1.3 , pz) ;
    
    float noisex3 = px + 4.0 * ofNoise(noisex + 1.7 , noisey + 9.2);
    float noisey3 = py + 4.0 * ofNoise(noisex + 8.3 , noisey + 2.8);
    
    return ofNoise(noisex3,noisey3);
    
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    //    src.load("monroe.jpg");
    src.load("lenna.png");
    
    dist.allocate(src.getWidth(), src.getHeight(), src.getImageType());
    
    ofSetWindowShape(src.getWidth(), src.getHeight());
    
    pixelNoise(&src,&dist);
    src.update();
    dist.update();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()) +" "+ ofToString(factor));
    
//    pixelNoise(&dist,&dist,242,240,353,287);
//    pixelNoise(&dist,&dist,0,0,512,512);
    pixelNoise(&dist,&dist);
    src.update();
    dist.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    dist.draw(0,0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP){
        factor += 0.1;
    }else if(key == OF_KEY_DOWN){
        factor -= 0.1;
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
    cout<<x <<' '<<y <<endl;
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
