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
struct Transition{
    string e, Qs, Qf;
};
class InputHandler {
    
    FILE *ms;
    FILE *inf;
    const char **args;
    vector<string> input;
    
public:
    InputHandler(const char * argv[]); //open spec file
    ~InputHandler();
    //get specifications
    vector<string> getQ();
    vector<string> getE();
    vector<Transition> getd();
    string getq0();
    vector<string> getF();
    
    void getINF(); //open input file fill input vec
    string getInput(); //return next input
};

#endif /* inputhandler_hpp */
