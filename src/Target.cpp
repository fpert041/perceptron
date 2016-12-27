//
//  Target.cpp
//  Perceptron
//
//  Created by Francesco Perticarari on 19/12/2016.
//
//

#include "Target.hpp"

Target::Target(){
    size = ofRandom(10, 50);
    location = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    color = ofColor(ofRandom(10, 250), ofRandom(10, 250), ofRandom(10, 250));
}

void Target::draw(){
    ofSetColor(color);
    ofDrawEllipse(location.x, location.y, size, size);
}
