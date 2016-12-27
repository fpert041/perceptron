//
//  Vehicle.cpp
//  Perceptron
//
//  Created by Francesco Perticarari on 19/12/2016.
//
//

#include "Vehicle.hpp"

Vehicle::Vehicle(){
    location = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    
    velocity = ofVec2f(ofRandom(1)-0.5, ofRandom(1)-0.5);
    //velocity = ofVec2f(8,-8);
    
    acceleration = ofVec2f(0,0);
    maxSpeed = 4; //maximum velocity size (which must be limited for the vehicle to be realistic)
    maxStir = 0.05; //maximum stirring capacity (the harder the vehicle to str, the smaller the number)
    mass = 5; //this variable reduces acceleration when a force is applied (as in the real world)
    
    //>> train brain by observing error <<
    desiredTarget.push_back(ofGetWidth()/2); //test: try and make the agent want to go to the centre
    desiredTarget.push_back(ofGetHeight()/2);
    error.push_back(desiredTarget[0] - location.x); //compute the error (how far we are from goal)
    error.push_back(desiredTarget[1] - location.y);
}

Vehicle::Vehicle(vector<float>& desiredTarget){
    location = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    
    velocity = ofVec2f(ofRandom(1)-0.5, ofRandom(1)-0.5);
    //velocity = ofVec2f(8,-8);
    
    acceleration = ofVec2f(0,0);
    maxSpeed = 4; //maximum velocity size (which must be limited for the vehicle to be realistic)
    maxStir = 0.05; //maximum stirring capacity (the harder the vehicle to str, the smaller the number)
    mass = 5; //this variable reduces acceleration when a force is applied (as in the real world)
    
    //>> train brain by observing error <<
    this->desiredTarget = desiredTarget;
    error.push_back(desiredTarget[0] - location.x); //compute the error (how far we are from goal)
    error.push_back(desiredTarget[1] - location.y);
}

//--------------------------------------------------------------


void Vehicle::draw(){
    
    cout << desiredTarget[0] << endl;
    
    ofPushMatrix(); //save current coordinate system
    ofTranslate(location.x, location.y); //translate origin by location vector
    
    //cout << -velocity.angle(ofVec2f(0,1)) << " / " << velocity.x << endl; //debug
    if(velocity.x<0){ //this condition is necessary to avoid "jumps" when the desired velocity is a vector with an angle bigger than PI relative to the current velocity
        ofRotateZ(-velocity.angle(ofVec2f(0,-1))); //rotate coord. system to match motion direction (velocity)
    } else {
        ofRotateZ(360-velocity.angle(ofVec2f(0,-1))); //rotate coord. system to match motion direction (velocity)
    }
    
    ofSetColor(0);
    ofDrawTriangle(0, 0, -15, 35, 15, 35); //draw triangle
    ofPopMatrix(); //revert general coordinare system (pop it back)
}

//--------------------------------------------------------------


void Vehicle::update(){
    
    velocity.operator+=(acceleration);
    velocity.normalize(); //make sure the max speed is respected
    velocity.operator*=(maxSpeed);
    
    location.operator+=(velocity);
    acceleration *= (0); //reset acceleration at the end of each loop (there is only acc. if there is any force pushing)
}

//--------------------------------------------------------------


 //      -----A WAY TO TAKE ALL THE TARGETS IN AND CHASE THEM-----(deprecated)
   // *  This method does not give the agent the power of choosing  *
   //  >>   often the agent gets STUCK among contrasting forces   <<
   //  *    How to make it an adaptable agent???  * (pss... NN!)  *

void Vehicle::steer(vector<ofVec2f>& targetsLocations){
    ofVec2f force;
    
    for (auto target : targetsLocations){ //for each target in an array of targets (identified by ofVector coordinates):
        force = seek(target); //-define a steering force
        applyForce(force); //-apply steering force to vehicle
    }
}


//--A BETTER WAY TO TAKE ALL THE TARGETS IN AND CHASE THEM--
// *This works as a simple but adapltable brain for our vehicle*

void Vehicle::intelliSteer(vector<ofVec2f>& targetsLocations){
    
    //>> stir using brain <<
    forces = vector<ofVec2f>(targetsLocations.size()); //make an array of inputs for our brain (= it will need to store all the steering forces)
    forcesFloat = vector<float>(forces.size()*2); //make an array of inputs translated in simple floats
    
    for(int i=forces.size()-1; i>=0; --i){ //fill in the array with steering forces
        forces[i] = intelliSeek(targetsLocations[i]);
        forcesFloat.push_back(forces[i].x);//...and convert to an array of floats
        forcesFloat.push_back(forces[i].y); //...double the size
    }
    
    brain.setup(forcesFloat);//reset the brain to fit the input IF NECESSARY
    
    vector<float> output = brain.feedFwd(forcesFloat, NOACTIV, 2); //send input thorough the brain as a pir of coordinates
    ofVec2f smartForce = ofVec2f(output[0], output[1]); //use resulting brain output to package a physical ofVector
    applyForce(smartForce); //use physical vector as a force and apply it to stir the vehicle
    
    //update error
    error[0]=desiredTarget[0] - location.x;
    error[1]=desiredTarget[1] - location.y;
    //cout<< "err: " << error[0] << " " <<error[1] <<endl; //debug
    
    brain.train(forcesFloat, error); //the brain is trained according to the error and the forces (here to try and get to the centre)
    
}



//--------------------------------------------------------------
// HELPER FUNCTIONS


void Vehicle::applyForce(ofVec2f force){
    //F=ma
    acceleration.operator+=(force.operator/=(mass));
}


ofVec2f Vehicle::seek(ofVec2f& targetLocation){ //returns a 2D physical vector representing a force steering towards a target
    
    ofVec2f desiredVelocity = targetLocation - location; // -calculate the physical vector from vehicle to target
    
    
    float d = sqrt(pow(desiredVelocity.x, 2) + pow(desiredVelocity.y, 2)); //weight the vector based on the distance to target
    float weight = d / ofGetWidth() * 100; //the closer the target...
    desiredVelocity.operator/=(pow(weight,2)); //...the stronger the desired velocity towards it (by a quadratic factor)

    
    desiredVelocity.normalize(); //make sure the max speed is respected
    desiredVelocity.operator*=(maxSpeed);
    
    
    if(d<10) {
        desiredVelocity.operator*=(0); //if the vehicle gets really close, stop the chase
    } else if (d > 1000) {
        return ofVec2f(0, 0); //if the vehicle gets too far, ignore tsrget
    }
    
    
    // -calculate the steering force -> {steering force = desired velocity - current velocity}
    ofVec2f force = desiredVelocity - velocity;
    force.limit(maxStir);
    
    return force; //-return steering force as a physical vector
}


ofVec2f Vehicle::intelliSeek(ofVec2f& targetLocation){ //returns a 2D physical vector representing a force steering towards a target
    
    ofVec2f desiredVelocity = targetLocation - location; // -calculate the physical vector from vehicle to target
    
    desiredVelocity.normalize(); //make sure the max speed is respected
    desiredVelocity.operator*=(maxSpeed);
    
    
    // -calculate the steering force -> {steering force = desired velocity - current velocity}
    ofVec2f force = desiredVelocity - velocity;
    force.limit(maxStir);
    
    return force; //-return steering force as a physical vector
}

