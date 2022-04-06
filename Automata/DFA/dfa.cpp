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
    
//    for(int i = 0; i < controller->Q.size(); i++)
//        cout << controller->Q.at(i) << ",";
//    cout << endl;
    
    cout << "[DFA]: requesting E.." <<endl;
    controller->E = inhandler->getE();
    
//    for(int i = 0; i < controller->E.size(); i++)
//        cout << controller->E.at(i) << ",";
//    cout << endl;
    
    cout << "[DFA]: requesting d.." <<endl;
    controller->d = inhandler->getd();
    
//    for(int i = 0; i < controller->d.size(); i++)
//    {
//        cout << controller->d.at(i).Qs << " ";
//        cout << controller->d.at(i).e << " ";
//        cout << controller->d.at(i).Qf << endl;
//    }
    
    cout << "[DFA]: requesting q0.." <<endl;
    controller->q0 = inhandler->getq0();
    
//    cout << controller->q0 << endl;
    
    cout << "[DFA]: requesting F.." <<endl;
    controller->F = inhandler->getF();
    
//    for(int i = 0; i < controller->F.size(); i++)
//        cout << controller->F.at(i) << ",";
//    cout << endl;
    
    cout << "[DFA]: checking Q.. ";
    if(controller->Q.size()>0)
    {
        cout << "[ok]" <<endl;
    }
    else
    {
        cout << "[bad]" <<endl;
        exit(1);
    }
    cout << "[DFA]: checking E.. ";
    if(controller->E.size()>0)
    {
        cout << "[ok]" <<endl;
    }
    else
    {
        cout << "[bad]" <<endl;
        exit(1);
    }
    cout << "[DFA]: checking d.. ";
    if(controller->d.size()>0)
    {
        cout << "[ok]" <<endl;
    }
    else
    {
        cout << "[bad]" <<endl;
        exit(1);
    }
    cout << "[DFA]: checking q0.. ";
    if(controller->q0.size()>0)
    {
        cout << "[ok]" <<endl;
    }
    else
    {
        cout << "[bad]" <<endl;
        exit(1);
    }
    cout << "[DFA]: checking F.. ";
    if(controller->F.size()>0)
    {
        cout << "[ok]" <<endl;
    }
    else
    {
        cout << "[bad]" <<endl;
        exit(1);
    }
    
    cout << "[DFA]: passed checks.. " <<endl;
    cout << "[DFA]: Q: {";
    for(int i = 0; i < controller->Q.size(); i++)
    {
        cout << "[" << controller->Q.at(i) << "]";
        if(i != controller->Q.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: E: {";
    for(int i = 0; i < controller->E.size(); i++)
    {
        cout << "[" << controller->E.at(i) << "]";
        if(i != controller->E.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: d: {";
    for(int i = 0; i < controller->d.size(); i++)
    {
        cout << "[" << controller->d.at(i).Qs << ", ";
        cout << controller->d.at(i).e << ", ";
        cout << controller->d.at(i).Qf << "]";
        if(i != controller->d.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: q0: {";
    cout << "[" << controller->q0 << "]}\n";
    cout << "[DFA]: F: {";
    for(int i = 0; i < controller->F.size(); i++)
    {
        cout << "[" << controller->F.at(i) << "]";
        if(i != controller->F.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: ready.." <<endl;
}
DFA::~DFA() //destructor
{
    delete controller;
    delete inhandler;
}
void DFA::run()
{
    
    cout << "[DFA]: running" << endl;
    inhandler->getINF();
    cout << "[DFA]: .." << endl;
    string currState = controller->q0;
    
    string nextState;
    
    string in = inhandler->getInput();
    while(!in.empty())
    {
        cout << "[DFA]: CURRENT STATE: " << currState <<endl;
        cout << "[DFA]: READ: " << in <<endl;
        
        bool tran = false;
        for(int i = 0; i < controller->d.size(); i++)
        {
            Transition tmp = controller->d.at(i);
            if(tmp.Qs == currState && tmp.e == in)
            {
                tran = true;
                cout << "[DFA]: TRANSITION: " << tmp.Qs << " " << tmp.e << " -> " << tmp.Qf <<endl;
                nextState = tmp.Qf;
            }
        }
        
        if(tran)
        {
            currState = nextState;
            in = inhandler->getInput();
            cout << "[DFA]: .." <<endl;
        }
        else
        {
            in = "";
            cout << "[DFA]: NO TRANSITION" <<endl;
        }
    }
    
    bool acc = false;
    for(int i = 0; i < controller->F.size(); i++)
    {
        if(currState == controller->F.at(i))
        {
            acc = true;
        }
    }
    
    if(acc)
    {
        cout << "[DFA]: ACCEPT" <<endl;
    }
    else
    {
        cout << "[DFA]: REJECT" <<endl;
    }
    
}
