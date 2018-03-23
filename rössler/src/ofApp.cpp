#include "ofApp.h"

void ofApp::rossler(float a,float b,float c,float scale,int count, float* weight){
    points.clear();
    indices.clear();
    Color.clear();
    x=0.15;
    y=0.1;
    z=0.13;
    w_r = weight[0];
    w_g = weight[1];
    w_b = weight[2];
    
    for(int i=0;i<count;i++){
        
        xn = -y-z;
        yn = x + a*y;
        zn = b + x*z - c*z ;
        
        x=xn;
        y=yn;
        z=zn;
        
        r = ofNoise(x) * w_r;
        g = ofNoise(y) * w_g;
        bl = ofNoise(z) * w_b;
    
        /*
        r = 0.6+2*log(abs(10*x));
        g = 0.5-0.1*x-z+ofNoise(y);
        bl = 0.4+z+5*ofNoise(z+y);
        */
        
        /*
        float r = 0.5+abs(sin(10*x));
        float g = 0.6-x-z;
        float b = 0.4+10*z;
        */
        
        col = ofFloatColor(r,g,bl,0.85);
        points.push_back(scale*ofVec3f(x,y,z));
        indices.push_back(i);
        Color.push_back(col);
    }
    vbo.setVertexData(&points[0], (int)points.size(), GL_DYNAMIC_DRAW);
    vbo.setIndexData(&indices[0], (int)indices.size(), GL_DYNAMIC_DRAW);
    vbo.setColorData(&Color[0], (int)Color.size(), GL_DYNAMIC_DRAW);

}


void ofApp::aChanged(float & a){
    rossler(a,b,c,scale,count,w);
}

void ofApp::bChanged(float & b){
    rossler(a,b,c,scale,count,w);
}

void ofApp::cChanged(float & c){
    rossler(a,b,c,scale,count,w);
}

void ofApp::scaleChanged(float & scale){
    rossler(a,b,c,scale,count,w);
}

void ofApp::countChanged(int & count){
    rossler(a,b,c,scale,count,w);
}

void ofApp::colorChanged(float &w){
//    w[0] = w_r; w[1] = w_g; w[2] = w_b;
    rossler(a,b,c,scale,count,&w);
}

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(1000);
//    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofSetCircleResolution(16);
    
    a.addListener(this, &ofApp::aChanged);
    b.addListener(this, &ofApp::bChanged);
    c.addListener(this, &ofApp::cChanged);
    scale.addListener(this, &ofApp::scaleChanged);
    count.addListener(this, &ofApp::countChanged);
//    w.addListener(this, &ofApp::colorChanged);
    
    
    gui.setup();
    gui.add(a.set("a",-1.065,-1.5,1.5));
    //gui.add(b.set("b",-0.013,-0.1,-0.01));
    gui.add(b.set("b",-0.013,-0.015,-0.005));
    gui.add(c.set("c",1.06,1.0,1.5));
    gui.add(scale.set("scale",500,10,1000));
    gui.add(count.set("count",300000,10,5000000));
    gui.add(w_r.set("Red Weight",1.00,0.00,3.00));
    gui.add(w_g.set("Green Weight",1.00,0.00,3.00));
    gui.add(w_b.set("Blue Weight",1.00,0.00,3.00));
    w[0] = w_r; w[1] = w_g; w[2] = w_b;
    
    rossler(a,b,c,scale,count,w);
//    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(90,90,90), ofColor(10,10,40),OF_GRADIENT_BAR);
    //linear bar circular
    cam.begin();
    if(bRotate){
        ofRotateX(rotate_x);
        ofRotateY(rotate_y);
        rotate_x+=0.1;
        rotate_y+=0.1;
    }
    
    if(bF1){
        if(a>=0.165)counts=0;
        a = -0.09;
        b = -0.086;
        c = 1.03;
        scale = 565;
        
        if(a<0.165) a = -0.09+((0.165+0.09)*counts/100);
        if(b>-0.27) b = -0.086+((-0.27+0.086)*counts/100); counts++;
        rossler(a,b,c,scale,count,w);
    }
    
    vbo.drawElements(GL_POINTS, (int)points.size() );
//    vbo.draw(GL_POINTS,0,(int)points.size()); //also ok
    
//        glVertexPointer(3,GL_FLOAT,0,&(points[0].x) );
    //    ofSetColor(200,100);
//    glColor3f(0xE0, 0xE0, 0x60);
//    glDrawArrays(GL_POINTS, 0, (int)points.size()  );
    //    ofSetColor(40,0,200);
    //    glDrawArrays(GL_POINTS, (int)points.size()/2,(int)points.size() );
    
    //    for(int i=0; i<100 ; i++){
    //    ofSetColor(255);
    //    glDrawArrays(GL_POINTS, i, i+1 );
    //    }

    cam.end();
    ofDisableDepthTest();
    if(showGui)gui.draw();
    if(bHide)ofDrawCircle(ofGetMouseX(),ofGetMouseY(), 5);
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == '0'){
        a = -0.09;
        b = -0.086;
        c = 1.03;
        scale = 565;
        rossler(a,b,c,scale,count,w);
    }else if(key == '1'){
        a = 0.165;
        b = -0.27;
        c = 1.0225;
        scale = 435;
        rossler(a,b,c,scale,count,w);
    } else if(key == '2'){
        a = 0.7;
        b = -0.35;
        c = 1.06;
        scale = 500;
        rossler(a,b,c,scale,count,w);
    }else if (key =='3'){
        a = 0.75925;
        b = 0.775;
        c = 1.2175;
        scale = 555;
        rossler(a,b,c,scale,count,w);
    }else if(key == '4'){
        a = 0.002;
        b = -0.028;
        c = 1.032;
        scale = 265;
        rossler(a,b,c,scale,count,w);
    }else if(key == '5'){
        a = -0.015;
        b = 0.06;
        c = 1.06;
        scale = 500;
        rossler(a,b,c,scale,count,w);
    }else if(key == '6'){
        a = 1.15885;
        b = 0.55;
        c = 1.39;
        scale = 405;
        rossler(a,b,c,scale,count,w);
    }else if(key == '7'){
        a = -0.555;
        b = -0.009;
        c = 1.025;
        scale = 570;
        rossler(a,b,c,scale,count,w);
    }else if(key == '8'){
        a = 0.465;
        b = 0.51;
        c = 1.09;
        scale = 490;
        rossler(a,b,c,scale,count,w);
    }else if (key =='9'){
        a = -1.065;
        b = -0.013;
        c = 1.06;
        scale = 500;
        rossler(a,b,c,scale,count,w);
    }else if(key == 'f'){
        ofToggleFullscreen();
    }else if(key == 's'){
        ofImage img;
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.saveImage( ofGetTimestampString() + ".png");
    }else if(key == 'r') {
        bRotate = !bRotate;
    }else if(key ==OF_KEY_F1) {
        if(a>=0.165)counts=0;
        //if(b<=-0.27)counts=0;
        
        a = -0.09;
        b = -0.086;
        c = 1.03;
        scale = 565;
        
        if(a<0.165) a = -0.09+((0.165+0.09)*counts/300);
        if(b>-0.27) b = -0.086+((-0.27+0.086)*counts/300); counts++;
    }else if(key == 'n'){
        bF1 = !bF1;
    }else if(key == 'g'){
        showGui = !showGui;
    }else if(key =='c'){
        bHide = !bHide;
    }else if(key == 'R'){//do rossler
        rossler(a,b,c,scale,count,w);
    }else if(key == '+'){
        if(param=="a") a+=0.0010; if(param=="b") b+=0.0010; if(param=="c") c+=0.0010;
        rossler(a,b,c,scale,count,w);
    }else if(key == '-'){
        if(param=="a") a-=0.0010; if(param=="b") b-=0.0010; if(param=="c") c-=0.0010;
        rossler(a,b,c,scale,count,w);
    }else if(key == OF_KEY_LEFT){
        if(param=="a") param="c"; else if(param=="b") param="a"; else if(param=="c") param="b";
    }else if(key == OF_KEY_RIGHT){
        if(param=="a") param="b"; else if(param=="b") param="c"; else if(param=="c") param="a";
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
void ofApp::windowResized(int w, int h){
    //ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
