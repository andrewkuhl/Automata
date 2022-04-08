//
//  tm.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef tm_hpp
#define tm_hpp

#include "tminputhandler.hpp"
#include <future>

class TM {
    
    struct Controller{ //controller
        
        vector<string> Q; //set of states
        vector<string> E; //set of input characters
        vector<string> G; //set of stack characters
        vector<TMTransition> d; //set of transitions
        string q0; //start state
        vector<string> F; //set of final states
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    TMInputHandler* inhandler; //input handler obj
    
public:
    
    TM(const char * argv[]);
    ~TM();
    bool run(); //run function
    bool machine(string currState_,
             vector<string> input_,
             vector<TMTransition> transitions_, vector<string> stack_);
};

#endif /* tm_hpp */
