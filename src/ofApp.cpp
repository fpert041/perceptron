#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    perceptronTestSetup(); //<<PERCEPTRON_TEST
    
    intelliAgentSetup(); ////<<PERCEPTRON_DRIVEN_AGENT
}

float ofApp::f(float x){
    return 2*x+1; //a straight line equation
}

//--------------------------------------------------------------
void ofApp::update(){
    
    intelliAgentUpdate(); ////<<PERCEPTRON_DRIVEN_AGENT
}

//--------------------------------------------------------------
void ofApp::draw(){

    /* comment/uncomment as appropriate to display desired output: */
    
    //perceptronTest(); //<<PERCEPTRON_TEST
    intelliAgentDraw(); ////<<PERCEPTRON_DRIVEN_AGENT
}

/*
 Instead of using the supervised learning model above, can you train the neural network to find the right weights by using a genetic algorithm?
 */

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //std::cout << p1.feedFwd(point) << endl; //the answer of the perceptron! (1 = yes / -1 = no)
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------



void ofApp::intelliAgentUpdate(){
    
    //agent.steer(targetsLoc); //set the agent to stir towards the targets (example without perceptron-brain)
    agent.intelliSteer(targetsLoc); //set the agent to stir using its brain
    
    agent.update();
}

void ofApp::intelliAgentDraw(){
    targetsLoc[0] = ofVec2f(ofGetMouseX(), ofGetMouseY());
    agent.desiredTarget[0] = targetsLoc[0].x;
    agent.desiredTarget[1] = targetsLoc[0].y; //not the most elegant way to update the desired target location of our agent
    
    for(int i = 0; i<targets.size(); i++){
        targets[i].draw();
    }
    ofSetColor(220, 0, 0);
    ofDrawRectangle(targetsLoc[0].x, targetsLoc[0].y, 30, 30);
    ofSetColor(0);
    
    agent.draw();
}

void ofApp::intelliAgentSetup(){
    
    //goal = ofVec2f(ofRandom(ofGetWidth()/3)+ofGetWidth()/6, ofRandom(ofGetHeight()/3)+ofGetWidth()/6);
    for(int i=targets.size()-1; i>=0; i--){
        ofVec2f &tarLocRef = targets[i].location;
        //cout<< targets[i].location.y << " - " << targets[i].location.y <<endl; //debug
        targetsLoc.push_back(tarLocRef); //create a vector full of ofVector references to the locations of the Targets
    }
    
    
    goalFloat[0] = targetsLoc[0].x;
    goalFloat[1] = targetsLoc[0].y;
    agent = Vehicle(goalFloat); //set up an agent who's reward is obtained by minimising distance with goal (error)
                            //it will fo so by weighting up the attractive/repulsive force of each target as below
}


//--------------------------------------------------------------


void ofApp::perceptronTest(){ //test our perceptron by asking it to learn how to classify points (above or below a line)
    
    ofBackground(200, 200, 20);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    p1.train(training[count].inputs, training[count].answer); //retrieve pairs of recorded pairs of inputs and answers for training
    count = (count + 1) % training.size(); //for animation's sake we are training 1 point at a time
    
    
    for(int i = 0; i<count; i++){
        //stroke(0) in processing??? <<<
        float guess = p1.feedFwd(training[i].inputs); //store perceptron's guess (1 or -1) for each training point provided
        ofSetColor(255, 0, 0);
        
        if(guess> 0) ofNoFill(); //differentiate guesses (check how the algorithm adjustes itself the more the training it receives
        else ofFill();
        
        ofDrawEllipse(training[i].inputs[0], training[i].inputs[1], 8, 8);
    }
    ofSetColor(0, 100, 250);
    ofDrawLine((-ofGetHeight()/2-1.0)/2, -ofGetHeight()/2, (ofGetHeight()/2-1.0)/2, ofGetHeight()/2); //draw a blue line to see what the computer needs to learn
    
}

void ofApp::perceptronTestSetup(){
    point.push_back(50); //x
    point.push_back(-12); //y
    point.push_back(1);  //bias
    //std::cout << training.size() << endl; //debugging line
    
    count = 0;
    trainings = 2000; //n# of training points
    
    for (int i = 0; i<trainings; i++){ //make 2000 training points
        float x = ofRandom(-ofGetWidth()/2.0,ofGetWidth()/2.0);
        float y = ofRandom(-ofGetHeight()/2.0,ofGetHeight()/2.0);
        
        float answer = 1;   //is the correct answer 1 or -1?
        if(y<f(x)) answer = -1;
        
        vector<float> trainingPoint; //make a vector with the inputs required
        trainingPoint.push_back(x);
        trainingPoint.push_back(y);
        
        training.push_back(Trainer(trainingPoint, answer)); //fill the vector that stores Trainer objects
    }
}
 
 
