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
    char e;
    char Qs, Qf;
};
class InputHandler {
    
    FILE *fp;
    
public:
    InputHandler(const char * argv[]);
    ~InputHandler();
    vector<string> getQ();
    vector<string> getE();
    Transition* getd();
    string getq0();
    vector<string> getF();
    
};

#endif /* inputhandler_hpp */
