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
    
    struct Controller{ //controller
        
        vector<string> Q; //set of states
        vector<string> E; //set of input characters
        vector<Transition> d; //set of transitions
        string q0; //start state
        vector<string> F; //set of final states
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    InputHandler* inhandler; //input handler obj
    
public:
    
    DFA(const char * argv[]);
    ~DFA();
    bool run(); //run function
};

#endif /* dfa_hpp */
