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
    cout << "[DFA]: initialized" <<endl;
    cout << "[DFA]: initializing Controller.." <<endl;
    
    controller = new Controller(); //alloc controller
    
    cout << "[DFA]: parsing input.." <<endl;
    cout << "[DFA]: initializing InputHandler.." <<endl;
    
    inhandler = new InputHandler(argv); //alloc inhandler
    inhandler->getMS();
    cout << "[DFA]: requesting Q.." <<endl;
    
    controller->Q = inhandler->Q_; //loading Q
    
    cout << "[DFA]: requesting E.." <<endl;
    controller->E = inhandler->E_; //loading E

    cout << "[DFA]: requesting d.." <<endl;
    controller->d = inhandler->d_; //loading d
    
    cout << "[DFA]: requesting q0.." <<endl;
    controller->q0 = inhandler->q0_; //loading q0
    
    cout << "[DFA]: requesting F.." <<endl;
    controller->F = inhandler->F_; //loading F

    cout << "[DFA]: checking Q.. "; //check Q
    if(controller->Q.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << "[DFA]: checking E.. "; //check E
    if(controller->E.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[DFA]: checking d.. "; //check d
    if(controller->d.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[DFA]: checking q0.. "; //check q0
    if(controller->q0.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[DFA]: checking F.. "; //check F
    if(controller->F.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << "[DFA]: passed checks.. " <<endl; //if not exited pass!
    cout << "[DFA]: Q: {";
    for(int i = 0; i < controller->Q.size(); i++) //print Q
    {
        cout << "[" << controller->Q.at(i) << "]";
        if(i != controller->Q.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: E: {";
    for(int i = 0; i < controller->E.size(); i++) //print E
    {
        cout << "[" << controller->E.at(i) << "]";
        if(i != controller->E.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: d: {";
    for(int i = 0; i < controller->d.size(); i++) //print d
    {
        cout << "[" << controller->d.at(i).Qs << ", ";
        cout << controller->d.at(i).e << ", ";
        cout << controller->d.at(i).Qf << "]";
        if(i != controller->d.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: q0: {";
    cout << "[" << controller->q0 << "]}\n"; //print q0
    cout << "[DFA]: F: {";
    for(int i = 0; i < controller->F.size(); i++) //print F
    {
        cout << "[" << controller->F.at(i) << "]";
        if(i != controller->F.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DFA]: ready.." <<endl; //ready
}
DFA::~DFA() //destructor
{
    delete controller;
    delete inhandler;
}
bool DFA::run()
{
    cout << "[DFA]: running" << endl;
    inhandler->getINF(); //loading input file
    cout << "[DFA]: .." << endl;
    string currState = controller->q0; //set current state to start state
    
    string nextState;
    
    string in = inhandler->getInput(); //get input
    while(!in.empty()) //while input isnt empty ""
    {
        cout << "[DFA]: CURRENT STATE: " << currState <<endl;
        cout << "[DFA]: READ: " << in <<endl;
        
        bool tran = false;
        for(int i = 0; i < controller->d.size(); i++) //checks transition on
        {
            Transition tmp = controller->d.at(i);
            if(tmp.Qs == currState && tmp.e == in) //current state and input
            {
                tran = true; //if theres a transition
                cout << "[DFA]: TRANSITION: " << tmp.Qs << " " << tmp.e << " -> " << tmp.Qf <<endl;
                nextState = tmp.Qf;
            }
        }
        
        if(tran)
        {
            currState = nextState; //transition if theres transition
            in = inhandler->getInput();
            cout << "[DFA]: .." <<endl;
        }
        else
        {
            in = ""; //else reject
            cout << "[DFA]: NO TRANSITION" <<endl;
            return false;
        }
    }
    
    for(int i = 0; i < controller->F.size(); i++)
    {
        if(currState == controller->F.at(i))
        {
            return true;  //if end state is final accept
        }
    }
    return false; //else reject
}
