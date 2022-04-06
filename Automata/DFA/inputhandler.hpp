//
//  inputhandler.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef inputhandler_hpp
#define inputhandler_hpp
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Transition{ //transition obj
    string e, Qs, Qf;
};

class InputHandler {
    
    FILE *ms; //machine specification file ptr
    FILE *inf; //input file ptr
    
    const char **args; //argument copy ptr
    vector<string> input; //input vector
    
public:
    InputHandler(const char * argv[]); //open spec file
    ~InputHandler();
    
    //return specifications
    vector<string> getQ();
    vector<string> getE();
    vector<Transition> getd();
    string getq0();
    vector<string> getF();
    
    void getINF(); //open input file load input vec
    string getInput(); //return next input
};

#endif /* inputhandler_hpp */
