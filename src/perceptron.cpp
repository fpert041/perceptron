//
//  perceptron.cpp
//  Perceptron
//
//  Created by Francesco Perticarari on 08/12/2016.
//
//

#include "perceptron.hpp"

Perceptron::Perceptron(int n, float cons){
    std::srand(std::time(NULL)); // use current time as seed for random generator
    
    //create vectors on N size for inputs and weights
    inputs = std::vector<float>(n);
    weights = std::vector<float>(n);
    c = cons; //learning constant: the higher the constant the bigger the attempt of adgustment of the weights in training
    for(int i= 0; i<weights.size(); i++){ //initialise weights
        weights[i] = random()*2 - 1;
    }
    return this; //this is not necessary because the complier automatically makes this
};

Perceptron::Perceptron(int n){
    std::srand(std::time(NULL)); // use current time as seed for random generator
    
    //create vectors on N size for inputs and weights
    inputs = std::vector<float>(n);
    weights = std::vector<float>(n);
    c=0.01; //learning constant: the higher the constant the bigger the attempt of adgustment of the weights in training
    for(int i= 0; i<weights.size(); i++){ //initialise weights
        weights[i] = random()*2 - 1;
        
        //std::cout << weights[i] << std::endl; //debug
    }
    return this; //this is not necessary because the complier automatically makes this
};

Perceptron::Perceptron(void){
    std::srand(std::time(NULL)); // use current time as seed for random generator
    
    inputs = {12, 4, 0}; //x, y, bias
    c=0.01;
    for(int i= 0; i<inputs.size(); i++){
        weights.push_back(random()*2 - 1); //genereate inputs' weights
    }
    return this; //this is not necessary because the complier automatically makes this
};


Perceptron::~Perceptron(){
    //delete pointers here if needed
}


//---CLASS METHODS---

//-- reset-up --

void Perceptron::setup(std::vector<float> inputs){
    //check that the size inputs received is consistent with vector (array) of input memory slots
    if(inputs.size() != this->inputs.size()){ //if not, re-construct
        this->inputs = std::vector<float>(inputs.size());
        this->weights = std::vector<float>(inputs.size());
        for(int i= 0; i<weights.size(); i++){ //and re-initialise weights
            weights[i] = random()*2 - 1; //
        }
    } else { return; } //if so, return
}

//--guess/action--

float Perceptron::feedFwd(std::vector<float> inputs){
    float sum = 0;
    for(int i = 0; i<weights.size(); i++){
        sum += inputs[i] * weights[i]; //compute the sum of the inputs, each multiplied by its weight
        
    }
    return activate(sum);
};

float Perceptron::feedFwd(std::vector<float> inputs, enum Type t){
    float sum = 0;
    float out;
    //std::vector<float> outVec = std::vector<float>(2);
    
    switch(t)
    {
        case CONTINUOUS :
            for(int i = 0; i<weights.size(); i++){
                sum += inputs[i] * weights[i]; //compute the sum of the inputs, each multiplied by its weight
        
            }
            out = activateCont(sum, 0);
        break;
            
        case CHOICE :
            for(int i = 0; i<weights.size(); i++){
                sum += inputs[i] * weights[i]; //compute the sum of the inputs, each multiplied by its weight
                
            }
            out = activate(sum);
        break;
            
        case NOACTIV :
            for(int i = 0; i<weights.size(); i++){
                sum += inputs[i] * weights[i]; //compute the sum of the inputs, each multiplied by its weight
                
            }
            out = sum;
        break;

    }
    return out;
};

std::vector<float> Perceptron::feedFwd(std::vector<float> inputs, enum Type t, int dimensions){
    if(dimensions<2) dimensions = 2;
    
    float sum = 0; //running sum
    std::vector<float> out; //cpp vector to store output ( in n dimensions, out.size() = n )
    int count = 0; //var to keep group inputs in dimensional groups (using a while loop)
    
    switch(t)
    {
        case CONTINUOUS :
            while(count<dimensions){ //make sure you do the sum of inputs for each dmension
                for(int i = 0; i<weights.size(); i+=dimensions){
                    sum += inputs[i+count] * weights[i]; //compute the sum of the inputs, each multiplied by its weight
                    //note that not all weights are used: this is because the components (dimensions) of any input unit...
                    //...are best treated as one (thus being wighted the same - e.g.: in 2d X and Y comp. are 1 unit)
                }
                out.push_back(activateCont(sum, 0)); //store the sum of the inputs for each dimension in a vector index
                count++; //E.G: in a 2d case, all the even indeces of "inputs" will be added together into "sum"
                            //"sum" is then pushed_back onto "out" and the process is repeated for the odd indeces using "count" --> note: before computing each sum the inputs of any dimensions are weighted
            }
            break;
            
        case CHOICE :
            while(count<dimensions){
                for(int i = 0; i<weights.size(); i+=dimensions){
                    sum += inputs[i+count] * weights[i]; //compute the sum of the inputs, each multiplied by its weight
                }
                out.push_back(activate(sum));
                count++;
            }
            out.push_back(activate(sum));
            break;
            
        case NOACTIV :
            while(count<dimensions){
                for(int i = 0; i<weights.size(); i+=dimensions){
                    sum += inputs[i+count] * weights[i]; //M*// //compute the sum of the inputs, each multiplied by its weight
                }
                out.push_back(sum);
                count++;
            }
            break;
    }
    
    return out; //return vector of floats (each index is a dimenstion of the input/output values)
}

//--training--

void Perceptron::train(std::vector<float> inputs, float desired){ //adjust weights based on current output and desired outcome
    //NEW WEIGHT = WEIGHT + Δ_WEIGHT
    //NEW WEIGHT = WEIGHT + ERROR * INPUT * LEARNING CONSTANT
    float guess = feedFwd(inputs);
    float error = desired - guess;
    for(int i=0; i<weights.size();i++){
        weights[i] += error * inputs[i] * c;
    }
}

void Perceptron::train(std::vector<float> inputs, std::vector<float> error){
    //adjust weights based on current inputs, their weights and the error produced
    
    //Since the vehicle observes its own error, there is no need to calculate one:
    //--we can simply receive the error as an argument.
    //Notice how the change in weight is processed once for each dimension of the error (which has the same number of dimensions as the output)
    int dimensions = error.size();
    for(int i = 0; i<weights.size(); i+=dimensions){
        for(int j=0; j<dimensions; j++){
            /*if(i%20 == 0){
                std::cout<< "*>whgts[" <<i<< "]: " << weights[i]
                << " ins[" << j+i << "]: " << inputs[i+j];        //debug
            }*/
            
            weights[i] += c*error[j]*inputs[i+j]; //M*//
            
            /*if(i%18 == 0){;
                std::cout<< " nw Whgts [" <<i<< "]: " << weights[i] << " expr: " <<  c*error[j]*inputs[i+j] << std::endl;       //debug
            }*/
        }
    }
}

//---HELPER FUNCTIONS---


float Perceptron::activate(float weightedSum){ //activation function (here a discontinuous threshold funct.)
    if(weightedSum > 0){
        return 1; //yes
    } else {
        return -1; //no
    }
};

float Perceptron::activateCont(float weightedSum, float threshold){ //activation function (here a continuous threshold funct.)
    if(weightedSum > threshold){
        return weightedSum; //pass input onwards
    } else {
        return 0; //don't pass
    }
};

float Perceptron::random(){ //return a random number between 0 and 1
    double rand_var = std::rand();
    double output = (rand_var / RAND_MAX);
    return (float)output;
}

/* -------------------------------- *
//simple perceptron scheme (NN unit)

X -(*)weigth_1----
                  \
                   \
                    + + --> ( { activation func. } ) --(*)outWeigth[optional]-->
                   /  ^
                  /   |
Y -(*)weigth_2----    /
                     /
bias-(*)weigth_bias--

*/
