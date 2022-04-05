//
//  dfa.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef dfa_hpp
#define dfa_hpp

class DFA {
    
    struct Transition{
        char e;
        char Qs, Qf;
    };
    
    struct Control{
        char* Q;
        char* E; //dynamic alphabet
        Transition* d;
        char q0;
        char* F;
    };
    
    Control* control;
    
public:
    
    DFA();
    ~DFA();
};

#endif /* dfa_hpp */
