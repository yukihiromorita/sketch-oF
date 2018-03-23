//
//  Line.cpp
//  MondrianGenerator
//
//  Created by Yukihiro Morita on 2017/01/23.
//
//

#include "Line.h"
#include <stdio.h>
#include "ofMain.h"

Line::Line(int t, int p) {
  typ = t;
  pos = p;
  from = 0;
  if (t == 1)
    to = ofGetHeight();
  if (t == 2)
    to = ofGetWidth();
    
}

bool Line::check(vector<Line> lines, int margin) {
  vector<int> cross;
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i].typ == typ) {              //平行で
      if (abs(lines[i].pos - pos) < margin) //近すぎる線があったらfalse
        return false;
    } else {                                            //垂直で
      if (pos >= lines[i].from && pos <= lines[i].to) { //線が交わっていたら
        cross.push_back(lines[i].pos); //交わる線のposをcrossにpush
      }
    }
  }
  if (cross.size() > 2) { //両端以外に交点を持ったら
    std::sort(cross.begin(), cross.end());
    //    int j=3;
    int j =
        int(ofRandom(cross.size() - 2)); // crossからランダムで選んで(max以外)
    int k =
        (j + 1) + int(ofRandom(cross.size() - 1 - j)); // jより先の線を1本選ぶ
    //  int k = j + 1;
    from = cross[j];
    to = cross[k];
  }
  return true;
}

void Line::draw() {
  if (typ == 1) {
    ofDrawLine(pos, from, pos, to);
  } else if (typ == 2) {
    ofDrawLine(from, pos, to, pos);
  }
}

 void Line::print() {
//    std::string s = to_string(a);
    cout<<": type="+ to_string(typ)
    +",pos="+to_string(pos)+",from="+ofToString(from)+",to="+ofToString(to);
}
