//
//  LSystem.h
//  8_L-System
//
//  Created by Yukihiro Morita on 2017/12/30.
//
//

#ifndef LSystem_h
#define LSystem_h

// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// An LSystem has a starting sentence
// An a ruleset
// Each generation recursively replaces characteres in the sentence
// Based on the rulset

class Rule {
public:
    char a; //axiom init value
    string b; //rule
    
    Rule(char a_, string b_) {
        a = a_;
        b = b_;
    }
    
    char getA() {
        return a;
    }
    
    string getB() {
        return b;
    }
    
};

class LSystem {
public:
    
    string sentence;     // The sentence (a string)
//    stringbuf sentence;
//    Rule* ruleset;      // The ruleset (an array of Rule objects)
    vector<Rule> ruleset;
    int generation;      // Keeping track of the generation #
    
    // Construct an LSystem with a startin sentence and a ruleset
    LSystem() {
    }
    LSystem(string axiom, vector<Rule> r) {
        sentence = axiom;
        ruleset = r;
        generation = 0;
    }
    
    // Generate the next generation
    void generate() {
        // An empty stringBuffer that we will fill
//        stringbuf nextgen = new stringbuf();
        string nextgen;
        // For every character in the sentence
        for (int i = 0; i < sentence.length(); i++) {
            // What is the character
            char curr = sentence.at(i);
//            char curr = sentence.charAt(i);
            // We will replace it with itself unless it matches one of our rules
//            string replace = "" + curr;
            string replace{curr};
            // Check every rule            
            for (int j = 0; j < ruleset.size(); j++) {
//                char a = ruleset[j].getA();
                char a = ruleset[j].getA();
                // if we match the Rule, get the replacement string out of the Rule
                if (a == curr) {
                    replace = ruleset[j].getB();
                    break;
                }
            }
            // Append replacement string
//            nextgen.append(replace);
            nextgen += replace;
            
        }
        // Replace sentence
//        sentence = nextgen.tostring();
        sentence = nextgen;
        // Increment generation
        generation++;
    }
    
    string getSentence() {
        return sentence; 
    }
    
    int getGeneration() {
        return generation; 
    }
    
};



#endif /* LSystem_h */
