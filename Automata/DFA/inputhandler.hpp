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

struct Transition{
    char e;
    char Qs, Qf;
};
class InputHandler {
    
    FILE *fp;
    std::vector<char> buffer;
    
public:
    InputHandler(const char * argv[]);
    ~InputHandler();
    char* getQ();
    char* getE();
    Transition* getd();
    char getq0();
    char* getF();
    
};

#endif /* inputhandler_hpp */
