//
//  nfa.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.

#include "nfa.hpp"
#include <iostream>
 
using namespace std;

NFA::NFA(const char * argv[]) //constructor
{
    cout << "[NFA]: initialized" <<endl;
    cout << "[NFA]: initializing Controller.." <<endl;
    
    controller = new Controller(); //alloc controller
    
    cout << "[NFA]: parsing input.." <<endl;
    cout << "[NFA]: initializing InputHandler.." <<endl;
    
    inhandler = new NFAInputHandler(argv); //alloc inhandler
    inhandler->getMS();
    cout << "[NFA]: requesting Q.." <<endl;
    
    controller->Q = inhandler->Q_; //loading Q
    
    cout << "[NFA]: requesting E.." <<endl;
    controller->E = inhandler->E_; //loading E

    cout << "[NFA]: requesting d.." <<endl;
    controller->d = inhandler->d_; //loading d
    
    cout << "[NFA]: requesting q0.." <<endl;
    controller->q0 = inhandler->q0_; //loading q0
    
    cout << "[NFA]: requesting F.." <<endl;
    controller->F = inhandler->F_; //loading F

    cout << "[NFA]: checking Q.. "; //check Q
    if(controller->Q.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << "[NFA]: checking E.. "; //check E
    if(controller->E.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[NFA]: checking d.. "; //check d
    if(controller->d.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[NFA]: checking q0.. "; //check q0
    if(controller->q0.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[NFA]: checking F.. "; //check F
    if(controller->F.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << "[NFA]: passed checks.. " <<endl; //if not exited pass!
    cout << "[NFA]: Q: {";
    for(int i = 0; i < controller->Q.size(); i++) //print Q
    {
        cout << "[" << controller->Q.at(i) << "]";
        if(i != controller->Q.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[NFA]: E: {";
    for(int i = 0; i < controller->E.size(); i++) //print E
    {
        cout << "[" << controller->E.at(i) << "]";
        if(i != controller->E.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[NFA]: d: {";
    for(int i = 0; i < controller->d.size(); i++) //print d
    {
        cout << "[" << controller->d.at(i).Qs << ", ";
        cout << controller->d.at(i).e << ", ";
        cout << controller->d.at(i).Qf << "]";
        if(i != controller->d.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[NFA]: q0: {";
    cout << "[" << controller->q0 << "]}\n"; //print q0
    cout << "[NFA]: F: {";
    for(int i = 0; i < controller->F.size(); i++) //print F
    {
        cout << "[" << controller->F.at(i) << "]";
        if(i != controller->F.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[NFA]: ready.." <<endl; //ready
}
NFA::~NFA() //destructor
{
    delete controller;
    delete inhandler;
}
bool NFA::run()
{
    cout << "[NFA]: running" << endl;
    inhandler->getINF(); //loading input file
    cout << "[NFA]: .." << endl;
    string currState = controller->q0; //set current state to start state
    
    string nextState;
    
    string in = inhandler->getInput(); //get input
    while(!in.empty()) //while input isnt empty ""
    {
        cout << "[NFA]: CURRENT STATE: " << currState <<endl;
        cout << "[NFA]: READ: " << in <<endl;
        
        bool tran = false;
        for(int i = 0; i < controller->d.size(); i++) //checks transition on
        {
            NFATransition tmp = controller->d.at(i);
            if(tmp.Qs == currState && tmp.e == in) //current state and input
            {
                tran = true; //if theres a transition
                cout << "[NFA]: TRANSITION: " << tmp.Qs << " " << tmp.e << " -> " << tmp.Qf <<endl;
                nextState = tmp.Qf;
            }
        }
        
        if(tran)
        {
            currState = nextState; //transition if theres transition
            in = inhandler->getInput();
            cout << "[NFA]: .." <<endl;
        }
        else
        {
            in = ""; //else reject
            cout << "[NFA]: NO TRANSITION" <<endl;
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
