//
//  main.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#include <iostream>
#include "dfa.hpp"
using namespace std;

int main(int argc, const char * argv[]) {

    
    if(argc < 2)//no argument
    {
        cout << "[Main][Error]: no argument" << endl;
        return 1;
    }
    
    int m = atoi(argv[1]);//get argument as int
    
    switch(m)//switch(arg)
    {
        case 1://arg1 DFA
        {
            cout << "[Main]: initializing DFA..." << endl;
            DFA *dfa = new DFA(argv);
            break;
        }
        default:
            cout << "[Main][Error]: wrong argument" << endl; //other arg
    }
        
    return 0;
}
