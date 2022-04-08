//
//  pda.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef pda_hpp
#define pda_hpp

#include "pdainputhandler.hpp"
#include <future>

class PDA {
    
    struct Controller{ //controller
        
        vector<string> Q; //set of states
        vector<string> E; //set of input characters
        vector<PDATransition> d; //set of transitions
        string q0; //start state
        vector<string> F; //set of final states
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    PDAInputHandler* inhandler; //input handler obj
    
public:
    
    PDA(const char * argv[]);
    ~PDA();
    bool run(); //run function
    bool machine(string currState_,
             vector<string> input_,
             vector<PDATransition> transitions_);
};

#endif /* pda_hpp */
