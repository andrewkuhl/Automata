//
//  dfainputhandler.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef dfainputhandler_hpp
#define dfainputhandler_hpp
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct DFATransition{ //transition obj
    string e, Qs, Qf;
};

class DFAInputHandler {
    
    ifstream ms; //machine specification file ptr
    ifstream inf; //input file ptr
    
    const char **args; //argument copy ptr
    
    
    vector<string> input; //input vector
    
public:
    DFAInputHandler(const char * argv[]); //open spec file
    ~DFAInputHandler();
    
    vector<string> Q_;
    vector<string> E_;
    vector<DFATransition> d_;
    string q0_;
    vector<string> F_;
    
    void getMS(); //open spec file
    
    void getINF(); //open input file load input vec
    string getInput(); //return next input
};

#endif /* inputhandler_hpp */
