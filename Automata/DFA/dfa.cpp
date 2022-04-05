//
//  dfa.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.

#include "dfa.hpp"
#include <iostream>
 
using namespace std;

DFA::DFA(const char * argv[]) //constructor
{
//    char* Q_ , char* E_ , Transition* d_ ,
//    char q0_, char* F_ ;
    cout << "[DFA]: initialized" <<endl;
    cout << "[DFA]: initializing Controller.." <<endl;
    controller = new Controller();
    
    cout << "[DFA]: parsing input.." <<endl;
    cout << "[DFA]: initializing InputHandler.." <<endl;
    inhandler = new InputHandler(argv);
    cout << "[DFA]: requesting Q.." <<endl;
    controller->Q = inhandler->getQ();
    for(int i = 0; i < controller->Q.size(); i++)
        cout << controller->Q.at(i);
    cout << endl;
    cout << "[DFA]: requesting E.." <<endl;
    controller->E = inhandler->getE();
    for(int i = 0; i < controller->E.size(); i++)
        cout << controller->E.at(i);
    cout << endl;
    cout << "[DFA]: requesting d.." <<endl;
    controller->d = inhandler->getd();
    cout << "[DFA]: requesting q0.." <<endl;
    controller->q0 = inhandler->getq0();
    cout << "[DFA]: requesting F.." <<endl;
    controller->F = inhandler->getF();
}
DFA::~DFA() //destructor
{
    delete controller;
    delete inhandler;
}
