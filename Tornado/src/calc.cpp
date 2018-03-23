//
//  calc.cpp
//  
//
//  Created by Yukihiro Morita on 2016/05/16.
//
//

#include "calc.h"

Calc::Calc(){

}

void Calc::init(){
    bottom = ofVec3f(ofRandom(-10,10),0,(-10,10));//底を少し動かす
    h = 1;
//    k = 0.5;
}

void Calc::calcTornado(){

    for(t = 0; t < 100; t += ofRandom(0.08,0.12)){ //約10000回繰り返す
        ofSetColor(ofRandom(50,170),ofRandom(50,150),ofRandom(100,150),150);//色は改良の余地あり
        h += ofRandom(0.5,1.2);//高さをランダムに足す
        r = 5 + exp(0.007*h); //半径,竜巻っぽくするため指数関数を使用
        //r = pow(6,0.007*h);//y=e^xである必要はないのでy=6^xとかでもok
        //r = k * h;//直線でもいいけど竜巻っぽくない
        theta  = 2 * PI * t;//tが1増えると1周
        
        ofPushMatrix();
        ofTranslate(bottom);//竜巻の底
        ofTranslate(r*cos(theta),h-300,r*sin(theta));//円の式:x=rcosθ,y=rcosθ,高さ(y座標)は適当に調整
        ofDrawBox(10);//大きさ10の箱を描画,時間があればvboにしたい
        ofPopMatrix();
    }

}