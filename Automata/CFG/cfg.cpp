//
//  cfg.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.

#include "cfg.hpp"
#include <iostream>

 
using namespace std;

CFG::CFG(const char * argv[]) //constructor
{
    cout << "[CFG]: initialized" <<endl;
    cout << "[CFG]: initializing Controller.." <<endl;
    
    controller = new Controller(); //alloc controller
    
    cout << "[CFG]: parsing input.." <<endl;
    cout << "[CFG]: initializing InputHandler.." <<endl;
    
    inhandler = new CFGInputHandler(argv); //alloc inhandler
    inhandler->getMS();
    cout << "[CFG]: requesting Q.." <<endl;
    
    controller->Q = inhandler->Q_; //loading Q
    
    cout << "[CFG]: requesting E.." <<endl;
    controller->E = inhandler->E_; //loading E

    cout << "[CFG]: requesting d.." <<endl;
    controller->d = inhandler->d_; //loading d
    
    cout << "[CFG]: requesting q0.." <<endl;
    controller->q0 = inhandler->q0_; //loading q0
    
    cout << "[CFG]: requesting F.." <<endl;
    controller->F = inhandler->F_; //loading F

    cout << "[CFG]: checking Q.. "; //check Q
    if(controller->Q.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << "[CFG]: checking E.. "; //check E
    if(controller->E.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[CFG]: checking d.. "; //check d
    if(controller->d.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[CFG]: checking q0.. "; //check q0
    if(controller->q0.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[CFG]: checking F.. "; //check F
    if(controller->F.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << "[CFG]: passed checks.. " <<endl; //if not exited pass!
    cout << "[CFG]: Q: {";
    for(int i = 0; i < controller->Q.size(); i++) //print Q
    {
        cout << "[" << controller->Q.at(i) << "]";
        if(i != controller->Q.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[CFG]: E: {";
    for(int i = 0; i < controller->E.size(); i++) //print E
    {
        cout << "[" << controller->E.at(i) << "]";
        if(i != controller->E.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[CFG]: d: {";
    for(int i = 0; i < controller->d.size(); i++) //print d
    {
        cout << "[" << controller->d.at(i).Qs << ", ";
        cout << controller->d.at(i).e << ", ";
        cout << controller->d.at(i).Qf << "]";
        if(i != controller->d.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[CFG]: q0: {";
    cout << "[" << controller->q0 << "]}\n"; //print q0
    cout << "[CFG]: F: {";
    for(int i = 0; i < controller->F.size(); i++) //print F
    {
        cout << "[" << controller->F.at(i) << "]";
        if(i != controller->F.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[CFG]: ready.." <<endl; //ready
}
CFG::~CFG() //destructor
{
    delete controller;
    delete inhandler;
}
bool CFG::run()
{
    cout << "[CFG]: running" << endl;
    inhandler->getINF(); //loading input file
    cout << "[CFG]: .." << endl;
    
    string in = inhandler->getInput(); //get input
    
    //create thread that runs compute( q0, input, transitions)
    future<bool> thread = async(launch::async, &CFG::machine, this,  controller->q0, inhandler->input, vector<CFGTransition>());
    
    return thread.get(); //return output
}
bool CFG::machine(string currState_,
         vector<string> input_,
         vector<CFGTransition> transitions_)
{
    
    string nextState = "";
    while(!input_.empty()) //while input isnt empty ""
    {
        string in = "";
        
        for(int i = 0; i < controller->d.size(); i++)//checking for epsilon
        {
            CFGTransition tmp = controller->d.at(i);
            if(tmp.Qs == currState_ && tmp.e == "eps")
            {
                //start a thread on transition eps
                transitions_.push_back(tmp);
                future<bool> t = async(launch::async, &CFG::machine, this,  tmp.Qf, input_, transitions_);
                if(t.get()){
                    return true; //if it accepted return true;
                }//else continue
            }
        }
        
        in = input_.at(0);
        input_.erase(input_.begin());
        
        bool tran = false;
        vector<CFGTransition> transvec;
        for(int i = 0; i < controller->d.size(); i++) //checks transition on
        {
            CFGTransition tmp = controller->d.at(i);
            if(tmp.Qs == currState_ && tmp.e == in) //current state and input
            {
                tran = true; //if theres a transition
                transvec.push_back(tmp);
                
            }
        }
        
        if(tran)
        {
            if(transvec.size() > 1)//more than 1 transition
            {
                for(int k = 0; k < transvec.size(); k++)
                {
                    //for first elemnts in vector
                    if(k!=0)
                        transitions_.pop_back();
                    transitions_.push_back(transvec.at(k));
                    //start a thread on transition k
                    future<bool> t = async(launch::async, &CFG::machine, this,  transvec.at(k).Qf, input_, transitions_);
                    if(t.get()){
                        return true; //if it accepted return true;
                    }//else continue
                    
                }
            }
            else //1 transition
            {
                transitions_.push_back(transvec.back());
                nextState = transvec.back().Qf;
                currState_ = nextState; //transition if theres transition
                in = inhandler->getInput();
            }
        }
        else
        {
            in = ""; //else reject
            return false;
        }
    }//end while
    
    for(int i = 0; i < controller->F.size(); i++)
    {
        if(currState_ == controller->F.at(i))
        {
            for(int j = 0; j < transitions_.size(); j++)
            {
                cout << "[CFG]: TRANSITION: " << transitions_.at(j).Qs << " " << transitions_.at(j).e << " -> " << transitions_.at(j).Qf <<endl;
                cout << "[CFG]: .." << endl;
            }
            return true;  //if end state is final accept
        }
    }
    return false; //else reject
}
