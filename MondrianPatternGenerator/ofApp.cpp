#include "ofApp.h"

void ofApp::myFill(vector<Line> lines, int x, int y) {
  Line up = Line(2, -1);
  Line down = Line(2, -1);
  Line left = Line(1, -1);
  Line right = Line(1, -1);
  for (int i = 0; i < lines.size(); i++) {
    if (lines[i].typ == 1) { //縦
      if (x > lines[i].pos && y > lines[i].from &&
          y < lines[i].to) { // DLineがランダムxより右でランダムyがDLine上にあったら
        if (left.pos == -1 || left.pos < lines[i].pos) {
          left = lines[i];
        }
      }
      if (x < lines[i].pos && y > lines[i].from && y < lines[i].to) {
        if (right.pos == -1 || right.pos > lines[i].pos) {
          right = lines[i];
        }
      }
    } else { //横
      if (y > lines[i].pos && x > lines[i].from && x < lines[i].to) {
        if (up.pos == -1 || up.pos < lines[i].pos) {
            up = lines[i];
        }
      }
      if (y < lines[i].pos && x > lines[i].from && x < lines[i].to) {
        if (down.pos == -1 || down.pos > lines[i].pos) {
            down = lines[i];
        }
      }
    }
  }
  if (up.pos == -1 || down.pos == -1 || left.pos == -1 || right.pos == -1)
    return;
  else {
    int col = int(ofRandom(4));

    if (col == 0)
      ofSetColor(0, 0, 0); // black
    else if (col == 1)
      ofSetColor(200, 0, 0); // red
    else if (col == 2)
      ofSetColor(0, 0, 200); // blue
    else if (col == 3)
      ofSetColor(200, 200, 0); // yellow

    ofDrawRectangle(left.pos, up.pos, right.pos - left.pos, down.pos - up.pos);
  }
}

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowShape(W, H);
  ofSetFrameRate(1);
  ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update() {
  if (pause) {
    DrawLines.clear();
    int w = ofRandom(10, 16);
    int N = 160 / w;
      
    DrawLines.push_back(Line(1, 0)); //左 縦
    DrawLines.push_back(Line(1, W)); //右 縦
    DrawLines.push_back(Line(2, 0)); //上 横
    DrawLines.push_back(Line(2, H)); //下 横

    for (int i = 0; i < N; i++) {
      int t, p;

//       0~Wか0~Hのposがランダムな線をN本作って
      if (ofRandom(0, 2) > 1) {
        t = 1; // tate
        p = int(ofRandom(0, W));
      } else {
        t = 2;
        p = int(ofRandom(0, H));
      }

      Line l = Line(t, p);
        
      if (l.check(DrawLines, margin)) {
        DrawLines.push_back(l);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  
  int c = DrawLines.size();
  int M = int(ofRandom(c / 4, c / 3));//色を塗る数は本数の1/4~1/3からランダム
  for (int i = 0; i < M; i++) {
      myFill(DrawLines, ofRandom(W), ofRandom(H));
    }

  ofSetLineWidth(13);
  ofSetColor(0);
  for (int i = 0; i < DrawLines.size(); i++) {
    DrawLines[i].draw();
  }
    DrawLines.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == ' ')
    pause = !pause;
    if (key=='s') ofSaveFrame();
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
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
