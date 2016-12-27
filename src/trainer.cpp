//
//  trainer.cpp
//  Perceptron
//
//  Created by Francesco Perticarari on 09/12/2016.
//
//

#include "trainer.hpp"

Trainer::Trainer(std::vector<float> inputs, float a){
    this->inputs = inputs; //take the input values
    this->inputs.push_back(1); //add the bias
    answer = a; //take the desired outcome
    
    return this;
}
