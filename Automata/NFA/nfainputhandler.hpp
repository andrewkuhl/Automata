//
//  nfainputhandler.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#ifndef nfainputhandler_hpp
#define nfainputhandler_hpp
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct NFATransition{ //transition obj
    string e, Qs, Qf;
};

class NFAInputHandler {
    
    ifstream ms; //machine specification file ptr
    ifstream inf; //input file ptr
    
    const char **args; //argument copy ptr
    
    
    
    
public:
    NFAInputHandler(const char * argv[]); //open spec file
    ~NFAInputHandler();
    
    vector<string> input; //input vector
    
    vector<string> Q_;
    vector<string> E_;
    vector<NFATransition> d_;
    string q0_;
    vector<string> F_;
    
    void getMS(); //open spec file
    
    void getINF(); //open input file load input vec
    string getInput(); //return next input
};

#endif /* inputhandler_hpp */
