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

    
    if(argc < 4)//no argument
    {
        cout << "[Main][Error]: missing argument(s)" << endl;
        return 1;
    }
    
    int m = atoi(argv[1]);//get argument as int
    
    switch(m)//switch( machine type )
    {
        case 1://arg1 DFA
        {
            cout << "[Main]: initializing DFA.." << endl;
            
            DFA *dfa = new DFA(argv); //DFA constructor
            
            cout << "[Main]: running DFA.." << endl;
            
            if(dfa->run())// DFA run()
                cout << "[Main]: DFA accepts on input" <<endl;//if run returns true accept
            else
                cout << "[Main]: DFA rejects on input" <<endl;//else reject
            break;
        }
        default:
            cout << "[Main][Error]: wrong argument" << endl; //wrong arg
    }
        
    return 0;
}
