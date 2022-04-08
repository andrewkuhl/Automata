//
//  dtm.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef dtm_hpp
#define dtm_hpp

#include "dtminputhandler.hpp"
#include <future>

class DTM {
    
    struct Controller{ //controller
        
        vector<string> Q; //set of states
        vector<string> E; //set of input characters
        vector<string> G; //set of stack characters
        vector<DTMTransition> d; //set of transitions
        string q0; //start state
        string qaccept; //accepting state
        string qreject; //rejecting state
        
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    DTMInputHandler* inhandler; //input handler obj
    
public:
    
    DTM(const char * argv[]);
    ~DTM();
    bool run(); //run function
    bool machine(string currState_,
             vector<string> input_,
             vector<DTMTransition> transitions_, vector<string> stack_);
};

#endif /* dtm_hpp */
