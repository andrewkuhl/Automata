//
//  dtminputhandler.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#ifndef dtminputhandler_hpp
#define dtminputhandler_hpp
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct DTMTransition{ //transition obj
    string Qs, Qf, read, write, direction;
};

class DTMInputHandler {
    
    ifstream ms; //machine specification file ptr
    ifstream inf; //input file ptr
    
    const char **args; //argument copy ptr
    
    
    
    
public:
    DTMInputHandler(const char * argv[]); //open spec file
    ~DTMInputHandler();
    
    vector<string> input; //input vector
    
    vector<string> Q_;
    vector<string> E_;
    vector<string> G_;
    vector<DTMTransition> d_;
    string q0_;
    string qaccept_;
    string qreject_;
    
    void getMS(); //open spec file
    
    void getINF(); //open input file load input vec
    string getInput(); //return next input
};

#endif /* dtminputhandler_hpp */
