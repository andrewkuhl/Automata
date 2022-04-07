//
//  nfa.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef nfa_hpp
#define nfa_hpp

#include "nfainputhandler.hpp"

class NFA {
    
    struct Controller{ //controller
        
        vector<string> Q; //set of states
        vector<string> E; //set of input characters
        vector<NFATransition> d; //set of transitions
        string q0; //start state
        vector<string> F; //set of final states
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    NFAInputHandler* inhandler; //input handler obj
    
public:
    
    NFA(const char * argv[]);
    ~NFA();
    bool run(); //run function
};

#endif /* nfa_hpp */
