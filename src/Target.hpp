//
//  Target.hpp
//  Perceptron
//
//  Created by Francesco Perticarari on 19/12/2016.
//
//

#ifndef Target_hpp
#define Target_hpp

#include <stdio.h>
#include "ofMain.h"

class Target {
public:
    Target();
    void draw();
    
    ofVec2f location;
    float size;
    ofColor color;
};

#endif /* Target_hpp */
