//
//  Vehicle.hpp
//  Perceptron
//
//  Created by Francesco Perticarari on 19/12/2016.
//
//

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include <vector>
#include "perceptron.hpp"
#include "ofMain.h"


class Vehicle{
public:
    
    Vehicle();
    Vehicle(vector<float>& desiredTarget);
    
    vector<float> desiredTarget; //where to go to using the brain
    vector<float> error; // a var to store the error (vector distance to desired target)
    
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    vector<ofVec2f> forces; //an array of inputs for our brain (= it will need to store all the steering forces)
    vector<float> forcesFloat; //an array of inputs in a format which the brain can understand
    
    void steer(vector<ofVec2f>& targetsLocation);
    
    void intelliSteer(vector<ofVec2f>& targetsLocation);
    void train(vector<float> forcesFloat, vector<float> desired);
    
    ofVec2f intelliSeek(ofVec2f& targetLocation);
    ofVec2f seek(ofVec2f& targetLocation);
    void draw();
    void update();
    
private:
    void applyForce(ofVec2f force);
    Perceptron brain = Perceptron(4, 0.01);
    float maxSpeed;
    float maxStir;
    float mass;
};

#endif /* Vehicle_hpp */
