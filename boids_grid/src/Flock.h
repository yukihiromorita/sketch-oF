#ifndef Flock_h
#define Flock_h
class Flock{
public:
    vector<Boid> boids; // An ArrayList for all the boids
    
    Flock() {
//        boids = vector<Boid>(); // Initialize the ArrayList
    }
    
    void run() {
        for (Boid& b : boids) {
            b.run(boids);  // Passing the entire list of boids to each boid individually
        }
    }
    
    void addBoid(Boid b) {
        boids.push_back(b);
    }
};

#endif /* Flock_h */
