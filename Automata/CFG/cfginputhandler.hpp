//
//  cfginputhandler.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#ifndef cfginputhandler_hpp
#define cfginputhandler_hpp
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct CFGTransition{ //transition obj
    string v;
    vector<string> rule;
};

class CFGInputHandler {
    
    ifstream ms; //machine specification file ptr
    ifstream inf; //input file ptr
    
    const char **args; //argument copy ptr
    
    
    
    
public:
    CFGInputHandler(const char * argv[]); //open spec file
    ~CFGInputHandler();
    
    vector<string> input; //input vector
    
    vector<string> V_;
    vector<string> E_;
    vector<CFGTransition> R_;
    string S_;
    
    void getMS(); //open spec file
    
    void getINF(); //open input file load input vec
    string getInput(); //return next input
};

#endif /* cfginputhandler_hpp */
