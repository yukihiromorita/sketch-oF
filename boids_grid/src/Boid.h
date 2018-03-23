#ifndef boid_h
#define boid_h
#include "ofMain.h"
#include "FlowField.h"
#include "Path.h"

class Boid{
public:
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float r;
    float maxforce;    // Maximum steering force
    float maxspeed;    // Maximum speed
    float sepWeight,aliWeight,cohWeight;
    
    Boid(float x, float y) {
        acceleration.set(0,0);
        float velx,vely;
        do{
            velx = ofRandom(-1,1);
            vely = ofRandom(-1,1);
        }while(velx == 0 && vely == 0);
        
        velocity = ofVec2f(velx,vely );
        position = ofVec2f(x,y);
        r = 6;
        maxspeed = 3;
        maxforce = 0.4;
        sepWeight = 1.5;
        aliWeight = 1.;
        cohWeight = 1.;
    }
    
    void run(vector<Boid> boids){
        flock(boids);
        update();
        display();
    }
    
    void update() {
        velocity += acceleration;
        velocity.limit(maxspeed);
        position += velocity;
        acceleration *= 0.;
        border();
    }
    
    void applyForce(ofVec2f force) {
        // We could add mass here if we want A = F / M
        acceleration += force;
    }
    
    // A method that calculates a steering force towards a target
    // STEER = DESIRED MINUS VELOCITY
    ofVec2f seek(ofVec2f target) {
        ofVec2f desired = target - position;  // A vector pointing from the position to the target
        desired.scale(maxspeed);
        ofVec2f steer = desired - velocity;
        steer.limit(maxforce);  // Limit to maximum steering force
        return steer;
    }
    
    void arrive(ofVec2f target){
        ofVec2f desired = target - position;
        if(position.x < 25){
            desired = ofVec2f(maxspeed,velocity.y);
        }
        float d = desired.length();
        desired.getNormalized();
        if(d<100){
            float m = ofMap(d,0,100,0,maxspeed);
            desired *= m;
        }else{
            desired *= maxspeed;
        }
        
        ofVec2f steer = desired - velocity;
        steer.limit(maxforce);  // Limit to maximum steering force
        applyForce(steer);
    }
    
    void wander(){
        float len = 1;
        float r = 10;
        float theta = ofRandom(0,2*PI);
        ofVec2f nextPos = position + velocity * len;
        ofVec2f target = ofVec2f(nextPos.x +r  * cos(theta) , nextPos.y +r*sin(theta) );
        arrive(target);
    }
    
    void follow(FlowField flow){
        ofVec2f desired = flow.lookup(position);
        desired.scale(maxspeed);
        ofVec2f steer = desired - velocity;
        steer.limit(maxforce);  // Limit to maximum steering force
        applyForce(steer);
    }
    
    void follow(Path p){
        ofVec2f predict = velocity;
        predict.normalize();
        predict *= 50;
        ofVec2f predictPos = position + predict;
        
        ofVec2f normal = ofVec2f(0,0);
        ofVec2f target = ofVec2f(0,0);
        float worldRecord = 1000000;  // Start with a very high record distance that can easily be beaten
        
        for (int i = 0; i < p.points.size()-1; i++) {
            
            // Look at a line segment
            ofVec2f a = p.points[i];
            ofVec2f b = p.points[i+1];
            
            // Get the normal point to that line
            ofVec2f normalPoint = getNormalPoint(predictPos, a, b);
            // This only works because we know our path goes from left to right
            // We could have a more sophisticated test to tell if the point is in the line segment or not
            //            if (normalPoint.x < a.x || normalPoint.x > b.x) {
            if (normalPoint.x < min(a.x,b.x) || normalPoint.x > max(a.x,b.x) || normalPoint.y < min(a.y,b.y) || normalPoint.y > max(a.y,b.y)) {
                // This is something of a hacky solution, but if it's not within the line segment
                // consider the normal to just be the end of the line segment (point b)
                normalPoint = b;
            }
            
            float distance = predictPos.distance(normalPoint);
            // Only if the distance is greater than the path's radius do we bother to steer
            if (worldRecord > distance) {
                worldRecord = distance;
                normal = normalPoint;
                
                // Find target point a little further ahead of normal
                ofVec2f dir = b - a;
                dir.normalize();
                dir *= 10;  // This could be based on velocity instead of just an arbitrary 10 pixels
                target = normalPoint + dir;
            }
        }
        if(worldRecord > p.radius){
            seek(target);
        }
    }
    
    
    ofVec2f getNormalPoint(ofVec2f p, ofVec2f a, ofVec2f b) {
        // Vector from a to p
        ofVec2f ap = p - a;
        // Vector from a to b
        ofVec2f ab = b - a;
        ab.normalize(); // Normalize the line
        // Project vector "diff" onto line by using the dot product
        ab *= ap.dot(ab);
        ofVec2f normalPoint = a + ab;
        return normalPoint;
    }
    
    ofVec2f separate(vector< Boid > boids){
        float desiredseparation = r * 3;
        ofVec2f sum(0,0);
        int count = 0;
        
        for(Boid& other : boids){
            float d = position.distance(other.position);
            if( d > 0 && d < desiredseparation){
                ofVec2f diff = position - other.position;
                diff.normalize();
                diff /= d;
                sum += diff;
                count++;
            }
        }
        if(count > 0) {
            sum /= count;
            sum.scale(maxspeed);
            ofVec2f steer = sum - velocity;
            steer.limit(maxforce);
            return steer;
        }else{
            return ofVec2f(0,0);
        }
    }
    
    ofVec2f align (vector<Boid> boids) {
        float neighbordist = 50;
        ofVec2f sum = ofVec2f(0,0);
        int count = 0;
        
        for (Boid& other :boids) {
            float d = position.distance(other.position);
            if ((d > 0) && (d < neighbordist)) {
                sum += other.velocity;
                count++;
            }
        }
        if (count > 0) {
            sum /= (float)count;
            sum.normalize();
            sum *= maxspeed;
            ofVec2f steer = sum - velocity;
            steer.limit(maxforce);
            return steer;
        } else {
            return ofVec2f(0,0);
        }
    }
    
    ofVec2f cohesion (vector<Boid> boids) {
        float neighbordist = 50;
        ofVec2f sum = ofVec2f(0,0);   // Start with empty vector to accumulate all positions
        int count = 0;
        for (Boid& other : boids) {
            float d = position.distance(other.position);
            if ((d > 0) && (d < neighbordist)) {
                sum += other.position; // Add position
                count++;
            }
        }
        if (count > 0) {
            sum /= count;
            return seek(sum);  // Steer towards the position
        } else {
            return ofVec2f(0,0);
        }
    }
    
    void applyBehaviors(vector<Boid> boids){
        ofVec2f sepForce = separate(boids);
        ofVec2f seekForce = seek(ofVec2f(ofGetMouseX(),ofGetMouseY() ) );
        
        sepForce *= 1.5;
        seekForce *= 0.5;
        
        applyForce(sepForce);
        applyForce(seekForce);
    }
    
    void setWeight(float sep , float ali,float coh){
        sepWeight = sep;
        aliWeight = ali;
        cohWeight = coh;
    }
    
    void flock(vector<Boid> boids){
        ofVec2f sep = separate(boids);
        ofVec2f ali = align(boids);
        ofVec2f coh = cohesion(boids);
        
        sep *= sepWeight;
        ali *= aliWeight;
        coh *= cohWeight;
        
        applyForce(sep);applyForce(ali);applyForce(coh);
    }
    
    void display() {
        // Draw a triangle rotated in the direction of velocity
        float theta = ofRadToDeg(atan2(velocity.y, velocity.x)) + 90;
        ofSetColor(127);
        ofSetLineWidth(1);
        ofPushMatrix();
        ofTranslate(position.x,position.y);
        ofRotate(theta);
        ofBeginShape();
        ofVertex(0, -r*2);
        ofVertex(-r, r*2);
        ofVertex(r, r*2);
        //        ofendShape(CLOSE);
        ofEndShape();
        ofPopMatrix();
    }
    
    void border(){
        //        position.x = float( (ofGetWidth() +  (int)position.x )% ofGetWidth());
        //        position.y = float( (ofGetHeight() + (int)position.y )% ofGetHeight());
        
        int width = ofGetWidth();
        int height = ofGetHeight();
        
        if (position.x < 0) position.x = width;
        if (position.y < 0) position.y = height;
        if (position.x > width) position.x = 0;
        if (position.y > height) position.y = 0;
    }
    
    float getTheta(){
        float theta = ofDegToRad(atan(velocity.y / velocity.x));
        std::cout << "theta: "<<theta << std::endl;
    }
};


#endif /* boid_h */
