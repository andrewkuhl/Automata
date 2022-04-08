//
//  pdainputhandler.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#ifndef pdainputhandler_hpp
#define pdainputhandler_hpp
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct PDATransition{ //transition obj
    string e, Qs, Qf;
};

class PDAInputHandler {
    
    ifstream ms; //machine specification file ptr
    ifstream inf; //input file ptr
    
    const char **args; //argument copy ptr
    
    
    
    
public:
    PDAInputHandler(const char * argv[]); //open spec file
    ~PDAInputHandler();
    
    vector<string> input; //input vector
    
    vector<string> Q_;
    vector<string> E_;
    vector<PDATransition> d_;
    string q0_;
    vector<string> F_;
    
    void getMS(); //open spec file
    
    void getINF(); //open input file load input vec
    string getInput(); //return next input
};

#endif /* inputhandler_hpp */
