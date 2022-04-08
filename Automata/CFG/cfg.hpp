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
        
        vector<string> V; //set of variables
        vector<string> E; //set of terminals
        vector<CFGTransition> R; //set of rules
        string S; //start state
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    CFGInputHandler* inhandler; //input handler obj
    
public:
    CFG(const char * argv[]){}
    ~CFG(){}

};

#endif /* cfg_hpp */
