//
//  trainer.hpp //A TRAINER CLASS
//  Perceptron
//
//  Created by Francesco Perticarari on 09/12/2016.
//
//

#ifndef trainer_hpp
#define trainer_hpp

#include <stdio.h>
#include <vector>

//A Trainer for the NN: a container for the perceptron's inputs and the desired (know) answer (for those inputs)

class Trainer {
public:
    std::vector<float> inputs;
    float answer;
    
    Trainer(std::vector<float> inputs, float a);
};

#endif /* trainer_hpp */
