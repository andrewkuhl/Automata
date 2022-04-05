//
//  dfa.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef dfa_hpp
#define dfa_hpp

#include "inputhandler.hpp"

class DFA {
    
    struct Controller{
        char* Q;
        char* E; //dynamic alphabet
        Transition* d;
        char q0;
        char* F;
        
        Controller(){std::cout<<"[Controller]: initialized" <<std::endl;}
    };
    
    InputHandler* inhandler;
    Controller* controller;
    
public:
    
    DFA(const char * argv[]);
    ~DFA();
};

#endif /* dfa_hpp */
