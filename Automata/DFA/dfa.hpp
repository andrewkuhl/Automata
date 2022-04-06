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
        vector<string> Q;
        vector<string> E; //dynamic alphabet
        vector<Transition> d;
        string q0;
        vector<string> F;
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    };
    
    InputHandler* inhandler;
    Controller* controller;
    
public:
    
    DFA(const char * argv[]);
    ~DFA();
    bool run();
};

#endif /* dfa_hpp */
