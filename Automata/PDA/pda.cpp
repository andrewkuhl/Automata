//
//  pda.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.

#include "pda.hpp"
#include <iostream>

 
using namespace std;

PDA::PDA(const char * argv[]) //constructor
{
    cout << "[PDA]: initialized" <<endl;
    cout << "[PDA]: initializing Controller.." <<endl;
    
    controller = new Controller(); //alloc controller
    
    cout << "[PDA]: initializing InputHandler.." <<endl;
    
    inhandler = new PDAInputHandler(argv); //alloc inhandler
    inhandler->getMS();
    cout << "[PDA]: loading";
    
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
    controller->F = inhandler->F_; //loading F

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
    if(controller->F.size()>0)
    {
        cout << ".";
    }
    else
    {
        cout << "[bad F]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "\n[PDA]: done" <<endl;
    cout << "[PDA]: passed checks.. " <<endl; //if not exited pass!
    cout << "[PDA]: Q: {";
    for(int i = 0; i < controller->Q.size(); i++) //print Q
    {
        cout << "[" << controller->Q.at(i) << "]";
        if(i != controller->Q.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[PDA]: E: {";
    for(int i = 0; i < controller->E.size(); i++) //print E
    {
        cout << "[" << controller->E.at(i) << "]";
        if(i != controller->E.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[PDA]: G: {";
    for(int i = 0; i < controller->G.size(); i++) //print G
    {
        cout << "[" << controller->G.at(i) << "]";
        if(i != controller->G.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[PDA]: d: {";
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
    cout << "[PDA]: q0: {";
    cout << "[" << controller->q0 << "]}\n"; //print q0
    cout << "[PDA]: F: {";
    for(int i = 0; i < controller->F.size(); i++) //print F
    {
        cout << "[" << controller->F.at(i) << "]";
        if(i != controller->F.size()-1)
            cout << ", ";
    }
    cout << "}\n";
    cout << "[PDA]: ready.." <<endl; //ready
}
PDA::~PDA() //destructor
{
    delete controller;
    delete inhandler;
}
bool PDA::run()
{
    cout << "[PDA]: running" << endl;
    inhandler->getINF(); //loading input file
    cout << "[PDA]: .." << endl;
    
    string in = inhandler->getInput(); //get input
    
    //create thread that runs compute( q0, input, transitions)
    future<bool> thread = async(launch::async, &PDA::machine, this,  controller->q0, inhandler->input, vector<PDATransition>(), vector<string>());
    
    return thread.get(); //return output
}
bool PDA::machine(string currState_,
         vector<string> input_,
         vector<PDATransition> transitions_, vector<string> stack_)
{
    string nextState = "";
    for(int i = 0; i < controller->d.size(); i++)
    {//checking for epsilon transition on current state
        PDATransition tmp = controller->d.at(i);
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
            future<bool> thread = async(launch::async, &PDA::machine, this,  tmp.Qf, input_, transitions_, stack_);
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
        
        vector<PDATransition>temptrans;
        bool transition = false;
        for(int i = 0; i < controller->d.size(); i++)
        {//checking for transition on current state and input
            PDATransition tmp = controller->d.at(i);
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
                PDATransition tmp = temptrans.at(k);
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
                future<bool> thread = async(launch::async, &PDA::machine, this,  tmp.Qf, input_, transitions_, stack_);
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
    for(int i = 0; i < controller->F.size(); i++)
    {
        if(controller->F.at(i) == currState_)
        {
            for(int j = 0; j < transitions_.size(); j++)
            {
                PDATransition tmp = transitions_.at(j);
                cout << "[Machine]: F{ " << tmp.Qs << " " << tmp.Qf << " " << tmp.e << " " << tmp.popping << " -> " << tmp.pushing << " }" << endl;
                cout << "[Machine]: .." << endl;
            }
            return true;
        }
    }
    return false;
}
