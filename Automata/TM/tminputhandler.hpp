//
//  tminputhandler.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#ifndef tminputhandler_hpp
#define tminputhandler_hpp
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct TMTransition{ //transition obj
    string Qs, Qf, e, popping, pushing;
};

class TMInputHandler {
    
    ifstream ms; //machine specification file ptr
    ifstream inf; //input file ptr
    
    const char **args; //argument copy ptr
    
    
    
    
public:
    TMInputHandler(const char * argv[]); //open spec file
    ~TMInputHandler();
    
    vector<string> input; //input vector
    
    vector<string> Q_;
    vector<string> E_;
    vector<string> G_;
    vector<TMTransition> d_;
    string q0_;
    vector<string> F_;
    
    void getMS(); //open spec file
    
    void getINF(); //open input file load input vec
    string getInput(); //return next input
};

#endif /* inputhandler_hpp */
