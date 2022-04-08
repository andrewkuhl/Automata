//
//  dtm.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.

#include "dtm.hpp"
#include <iostream>

 
using namespace std;

DTM::DTM(const char * argv[]) //constructor
{
    cout << "[DTM]: initialized" <<endl;
    cout << "[DTM]: initializing Controller.." <<endl;
    
    controller = new Controller(); //alloc controller
    
    cout << "[DTM]: initializing InputHandler.." <<endl;
    
    inhandler = new DTMInputHandler(argv); //alloc inhandler
    inhandler->getMS();
    cout << "[DTM]: loading";
    
    controller->Q = inhandler->Q_; //loading Q
    
    cout << ".";
    controller->E = inhandler->E_; //loading E
    
    cout << ".";
    controller->G = inhandler->G_; //loading G

    cout << ".";
    controller->d = inhandler->d_; //loading d
    
    cout << ".";
    controller->q0 = inhandler->q0_; //loading q0
    
    cout << ".";
    controller->qaccept = inhandler->qaccept_; //loading qaccept
    
    cout << ".";
    controller->qreject = inhandler->qreject_; //loading reject

    cout << ".";
    if(controller->Q.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad Q]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << ".";
    if(controller->E.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad E]" <<endl; //empty [bad]
        exit(1);
    }
    cout << ".";
    if(controller->G.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad G]" <<endl; //empty [bad]
        exit(1);
    }
    cout << ".";
    if(controller->d.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad d]" <<endl; //empty [bad]
        exit(1);
    }
    cout << ".";
    if(controller->q0.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad q0]" <<endl; //empty [bad]
        exit(1);
    }
    cout << ".";
    if(controller->qaccept.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad qaccept]" <<endl; //empty [bad]
        exit(1);
    }
    if(controller->qreject.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad qreject]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "\n[DTM]: done" <<endl;
    cout << "[DTM]: passed checks.. " <<endl; //if not exited pass!
    cout << "[DTM]: Q: {";
    for(int i = 0; i < controller->Q.size(); i++) //print Q
    {
        cout << "[" << controller->Q.at(i) << "]";
        if(i != controller->Q.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DTM]: E: {";
    for(int i = 0; i < controller->E.size(); i++) //print E
    {
        cout << "[" << controller->E.at(i) << "]";
        if(i != controller->E.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DTM]: G: {";
    for(int i = 0; i < controller->G.size(); i++) //print G
    {
        cout << "[" << controller->G.at(i) << "]";
        if(i != controller->G.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DTM]: d: {";
    for(int i = 0; i < controller->d.size(); i++) //print d
    {
        cout << "[" << controller->d.at(i).Qs << ", ";
        cout << controller->d.at(i).Qf << ", ";
        cout << controller->d.at(i).e << ", ";
        cout << controller->d.at(i).popping << " -> ";
        cout << controller->d.at(i).pushing << "]";
        if(i != controller->d.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[DTM]: q0: {";
    cout << "[" << controller->q0 << "]}\n"; //print q0
    cout << "[DTM]: qaccept: {";
    cout << "[" << controller->qaccept << "]}\n"; //print qaccept
    cout << "[DTM]: qreject: {";
    cout << "[" << controller->qreject << "]}\n"; //print qreject
    cout << "[DTM]: ready.." <<endl; //ready
}
DTM::~DTM() //destructor
{
    delete controller;
    delete inhandler;
}
bool DTM::run()
{
    cout << "[DTM]: running" << endl;
    inhandler->getINF(); //loading input file
    cout << "[DTM]: .." << endl;
    
    string in = inhandler->getInput(); //get input
    
    //create thread that runs compute( q0, input, transitions)
    future<bool> thread = async(launch::async, &DTM::machine, this,  controller->q0, inhandler->input, vector<DTMTransition>(), vector<string>());
    
    return thread.get(); //return output
}
bool DTM::machine(string currState_,
         vector<string> input_,
         vector<DTMTransition> transitions_, vector<string> stack_)
{
    string nextState = "";
    for(int i = 0; i < controller->d.size(); i++)
    {//checking for epsilon transition on current state
        DTMTransition tmp = controller->d.at(i);
        if(tmp.Qs == currState_ && tmp.e == "eps")
        {
            //start thread on found transition
            //return true if true
            
            transitions_.push_back(tmp);
            
            string popped = "";
            if(!stack_.empty() && tmp.popping != "eps")
            {
                popped = stack_.back();
                //cout << "popped " << popped << endl;
                stack_.pop_back();
            }
            if(tmp.pushing != "eps")
            {
                stack_.push_back(tmp.pushing);
                //cout << "pushed " << tmp.pushing << endl;
            }
            //create thread that runs compute( nextState, input, previous transitions, stack)
            future<bool> thread = async(launch::async, &DTM::machine, this,  tmp.Qf, input_, transitions_, stack_);
            if(thread.get())
                return true; //return output
            else
            {
                transitions_.pop_back();
                if(tmp.pushing != "eps")
                    stack_.pop_back();
                if(tmp.popping != "eps")
                    stack_.push_back(popped);
            }
        }
    }
    while(!input_.empty()) //while input isnt empty ""
    {
        string in = "";
        in = input_.at(0);
        input_.erase(input_.begin());
        
        vector<DTMTransition>temptrans;
        bool transition = false;
        for(int i = 0; i < controller->d.size(); i++)
        {//checking for transition on current state and input
            DTMTransition tmp = controller->d.at(i);
            if(tmp.Qs == currState_ && tmp.e == in)
            {
                //add transition to list set transition true
                transition = true;
                temptrans.push_back(tmp);
            }
        }
        
        //if transition = true then transition
        //else return false no transition on input
        if(transition)
        {
            for(int k = 0; k < temptrans.size(); k++)
            {
                DTMTransition tmp = temptrans.at(k);
                //start thread on found transition
                //return true if true

                transitions_.push_back(tmp);
                
                string popped = "";
                if(!stack_.empty() && tmp.popping != "eps")
                {
                    popped = stack_.back();
                    //cout << "popped " << popped << endl;
                    stack_.pop_back();
                }
                if(tmp.pushing != "eps")
                {
                    stack_.push_back(tmp.pushing);
                    //cout << "pushed " << tmp.pushing << endl;
                }
                //create thread that runs compute( nextState, input, previous transitions, stack)
                future<bool> thread = async(launch::async, &DTM::machine, this,  tmp.Qf, input_, transitions_, stack_);
                if(thread.get())
                    return true; //return output
                else
                {
                    transitions_.pop_back();
                    if(tmp.pushing != "eps")
                        stack_.pop_back();
                    if(tmp.popping != "eps")
                        stack_.push_back(popped);
                }
            }
        }
        else
        {
            return false;
        }
        
    }//end while input ! empty
    
    if(controller->qaccept == currState_)
    {
        for(int j = 0; j < transitions_.size(); j++)
        {
            DTMTransition tmp = transitions_.at(j);
            cout << "[Machine]: F{ " << tmp.Qs << " " << tmp.Qf << " " << tmp.e << " " << tmp.popping << " -> " << tmp.pushing << " }" << endl;
            cout << "[Machine]: .." << endl;
        }
        return true;
    }
    return false;
}
