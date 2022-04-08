//
//  main.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#include <iostream>

#include "dfa.hpp"
#include "nfa.hpp"
#include "pda.hpp"
#include "cfg.hpp"

using namespace std;

void runDFA(const char * argv[]){
    cout << "[Main]: initializing DFA.." << endl;
    
    DFA *dfa = new DFA(argv); //DFA constructor
    
    cin.clear();
    cout << "[Main]: run DFA? [y/n]  ";
    string inp;
    cin >> inp;
    if(inp == "y")
    {
        do{
            cout << endl;
            cout << "[Main]: running DFA.." << endl;
            if(dfa->run())// DFA run()
                cout << "[Main]: DFA accepts on input" <<endl;//if run returns true accept
            else
                cout << "[Main]: DFA rejects on input" <<endl;//else reject
            
            cout << "[Main]: .." << endl;
            cout << "[Main]: run DFA again? [y/n]  ";
            cin >> inp;
        }while(inp == "y");
    }
}

void runNFA(const char * argv[]){
    cout << "[Main]: initializing NFA.." << endl;
    
    NFA *nfa = new NFA(argv); //NFA constructor
    
    cin.clear();
    cout << "[Main]: run NFA? [y/n]  ";
    string inp;
    cin >> inp;
    if(inp == "y")
    {
        do{
            cout << "[Main]: running NFA.." << endl;
            if(nfa->run())// NFA run()
                cout << "[Main]: NFA accepts on input" <<endl;//if run returns true accept
            else
                cout << "[Main]: NFA rejects on input" <<endl;//else reject
            
            cout << "[Main]: .." << endl;
            cout << "[Main]: run NFA again? [y/n]  ";
            cin >> inp;
        }while(inp == "y");
    }
}

void runPDA(const char * argv[]){
    cout << "[Main]: initializing PDA.." << endl;
    
    PDA *pda = new PDA(argv); //PDA constructor
    
    cin.clear();
    cout << "[Main]: run PDA? [y/n]  ";
    string inp;
    cin >> inp;
    if(inp == "y")
    {
        do{
            cout << "[Main]: running PDA.." << endl;
            if(pda->run())// PDA run()
                cout << "[Main]: PDA accepts on input" <<endl;//if run returns true accept
            else
                cout << "[Main]: PDA rejects on input" <<endl;//else reject
            
            cout << "[Main]: .." << endl;
            cout << "[Main]: run PDA again? [y/n]  ";
            cin >> inp;
        }while(inp == "y");
    }
}

int main(int argc, const char * argv[]) {

    
    if(argc < 3)//missing argument
    {
        cout << "[Main][Error]: missing argument(s)" << endl;
        return 1;
    }
    
    cout << "[Main]: choose machine.." << endl; //machine choice input
    cout << "[DFA].. \t[1]" << endl;
    cout << "[NFA].. \t[2]" << endl;
    cout << "[PDA].. \t[3]" << endl;
    cout << "[CFG].. \t[4]" << endl;
    cout << "[EXIT].. \t[0]" << endl;
    
    int m;
    cin >> m;
    
    switch(m)//switch( machine type )
    {
        case 1://1 DFA
        {
            runDFA(argv);
            break;
        }
        case 2://2 NFA
        {
            runNFA(argv);
            break;
        }
        case 3://3 PDA
        {
            runPDA(argv);
            break;
        }
        case 4://4 CFG
        {
            break;
        }
        default:
            cout << "[Main][Error]: wrong argument" << endl; //wrong arg
    }
        
    return 0;
}
