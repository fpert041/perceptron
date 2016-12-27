#pragma once

#include "perceptron.hpp"
#include "trainer.hpp"
#include "Vehicle.hpp"
#include "Target.hpp"
#include <vector>
#include "ofMain.h"


class ofApp : public ofBaseApp{

	public:
    
		void setup();
		void update();
        void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //--------------------------------
		
    void perceptronTestSetup(); //setup function for perceptron test
    void perceptronTest();
    //////////////////////
    Perceptron p1 = Perceptron(4); //create a Perceptron object with this type of constructor
    vector<Trainer> training; //vector of Trainer objects (which are containers for training sets)
    int trainings;  //n# of training input sets
    vector<float> point;
    int count;
    float f(float x); //straight line equation (for training perceptron test)
  
    //--------------------------------
    
    void intelliAgentUpdate();
    void intelliAgentDraw();
    void intelliAgentSetup();
    ////////////////////////
    Vehicle agent;
    ofVec2f goal;
    vector<Target> targets = vector<Target>(20);
    vector<ofVec2f> targetsLoc;
    vector<float> targetsLocFloats;
    vector<float> goalFloat = vector<float>(2);
    
};
