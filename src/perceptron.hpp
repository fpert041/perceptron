//
//  perceptron.hpp //A PERCEPTION TYPE
//  Perceptron
//
//  Created by Francesco Perticarari on 08/12/2016.
//
//

#ifndef perceptron_hpp
#define perceptron_hpp

#include <stdio.h>
#include <vector>
#include <random>
#include <iostream>


//PERCEPTRON: a Neural Network unit

enum Type { CONTINUOUS, CHOICE, NOACTIV};

class Perceptron {
public:
    
    Perceptron(); //constructor
    Perceptron(int n); //constructor
    Perceptron(int n, float cons); //constructor
    ~Perceptron(); //destructor -> useful to free up memory used by pointers
    
    //interface methods
    void setup(std::vector<float> inputs);
    float feedFwd(std::vector<float> inputs); //
    float feedFwd(std::vector<float> inputs, enum Type t); //
    std::vector<float> feedFwd(std::vector<float> inputs, enum Type t, int dimensions); //
    //(look into Templates to improve design of this multiple choice)(you can have function templates or class t.)
    
    void train(std::vector<float> inputs, float desired); //train with a goal-answer
    void train(std::vector<float> inputs, std::vector<float> error); //train with an error vector

    //interface variables
    std::vector<float> inputs;

private:
    
    //helper methods
    float activate(float weightedSum);
    float activateCont(float weightedSum, float threshold);
    float c; //learning constant
    std::vector<float> weights;
    float random(); //return random value between 0 and 1
};


#endif /* perceptron_hpp */
