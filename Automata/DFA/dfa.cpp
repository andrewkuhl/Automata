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
    cout << "[DFA]: initializing Controller..." <<endl;
    controller = new Controller();
    
    cout << "[DFA]: parsing input..." <<endl;
    cout << "[DFA]: initializing InputHandler..." <<endl;
    inhandler = new InputHandler(argv);
    controller->Q = inhandler->getQ();
    controller->E = inhandler->getE();
    controller->d = inhandler->getd();
    controller->q0 = inhandler->getq0();
    controller->F = inhandler->getF();
}
DFA::~DFA() //destructor
{
    delete controller;
    delete inhandler;
}
