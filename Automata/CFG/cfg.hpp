//
//  cfg.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef cfg_hpp
#define cfg_hpp

#include "cfginputhandler.hpp"
#include <future>

class CFG {
    
    struct Controller{ //controller
        
        vector<string> Q; //set of states
        vector<string> E; //set of input characters
        vector<CFGTransition> d; //set of transitions
        string q0; //start state
        vector<string> F; //set of final states
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    CFGInputHandler* inhandler; //input handler obj
    
public:
    
    CFG(const char * argv[]);
    ~CFG();
    bool run(); //run function
    bool machine(string currState_,
             vector<string> input_,
             vector<CFGTransition> transitions_);
};

#endif /* cfg_hpp */
