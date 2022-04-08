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
    
    cout << "[PDA]: parsing input.." <<endl;
    cout << "[PDA]: initializing InputHandler.." <<endl;
    
    inhandler = new PDAInputHandler(argv); //alloc inhandler
    inhandler->getMS();
    cout << "[PDA]: requesting Q.." <<endl;
    
    controller->Q = inhandler->Q_; //loading Q
    
    cout << "[PDA]: requesting E.." <<endl;
    controller->E = inhandler->E_; //loading E
    
    cout << "[PDA]: requesting G.." <<endl;
    controller->G = inhandler->G_; //loading G

    cout << "[PDA]: requesting d.." <<endl;
    controller->d = inhandler->d_; //loading d
    
    cout << "[PDA]: requesting q0.." <<endl;
    controller->q0 = inhandler->q0_; //loading q0
    
    cout << "[PDA]: requesting F.." <<endl;
    controller->F = inhandler->F_; //loading F

    cout << "[PDA]: checking Q.. "; //check Q
    if(controller->Q.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
    cout << "[PDA]: checking E.. "; //check E
    if(controller->E.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[PDA]: checking G.. "; //check G
    if(controller->G.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[PDA]: checking d.. "; //check d
    if(controller->d.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[PDA]: checking q0.. "; //check q0
    if(controller->q0.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    cout << "[PDA]: checking F.. "; //check F
    if(controller->F.size()>0)
    {
        cout << "[ok]" <<endl; //not empty [ok]
    }
    else
    {
        cout << "[bad]" <<endl; //empty [bad]
        exit(1);
    }
    
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
    while(!input_.empty()) //while input isnt empty ""
    {
        string in = "";
        
        for(int i = 0; i < controller->d.size(); i++)//checking for epsilon
        {
            PDATransition tmp = controller->d.at(i);
            if(tmp.Qs == currState_ && tmp.e == "eps")
            {
                //start a thread on transition eps
                
                transitions_.push_back(tmp);
                string popped;
                if(!stack_.empty() && stack_.back() == tmp.popping)
                {
                    if(tmp.pushing != "eps")
                    {
                        popped = stack_.back();
                        stack_.pop_back();
                    
                        stack_.push_back(tmp.pushing);
                        future<bool> t = async(launch::async, &PDA::machine, this,  tmp.Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                        stack_.pop_back();
                        stack_.push_back(popped);
                    }
                    else
                    {
                        popped = stack_.back();
                        stack_.pop_back();
                        future<bool> t = async(launch::async, &PDA::machine, this,  tmp.Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                        stack_.push_back(popped);
                    }
                }
                else if(tmp.popping == "eps")
                {
                    if(tmp.pushing != "eps")
                    {
                        stack_.push_back(tmp.pushing);
                        future<bool> t = async(launch::async, &PDA::machine, this,  tmp.Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                        stack_.pop_back();
                    }
                    else{

                        future<bool> t = async(launch::async, &PDA::machine, this,  tmp.Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                    }
                }
                else
                    return false;
                
                transitions_.pop_back();
            }
        }
        
        in = input_.at(0);
        input_.erase(input_.begin());
        
        bool tran = false;
        vector<PDATransition> transvec;
        for(int i = 0; i < controller->d.size(); i++) //checks transition on
        {
            PDATransition tmp = controller->d.at(i);
            if(tmp.Qs == currState_ && tmp.e == in) //current state and input
            {
                tran = true; //if theres a transition
                transvec.push_back(tmp);
                
            }
        }
        
        if(tran)
        {
            for(int k = 0; k < transvec.size(); k++)
            {

                //start a thread on transition k
                transitions_.push_back(transvec.at(k));
                string popped;
                if(stack_.back() == transvec.at(k).popping)
                {
                    if(transvec.at(k).pushing != "eps")
                    {
                        popped = stack_.back();
                        stack_.pop_back();
                    
                        stack_.push_back(transvec.at(k).pushing);
                        future<bool> t = async(launch::async, &PDA::machine, this,  transvec.at(k).Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                        stack_.pop_back();
                        stack_.push_back(popped);
                    }
                    else
                    {
                        popped = stack_.back();
                        stack_.pop_back();
                        future<bool> t = async(launch::async, &PDA::machine, this,  transvec.at(k).Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                        stack_.push_back(popped);
                    }
                }
                else if(transvec.at(k).popping == "eps")
                {
                    if(transvec.at(k).pushing != "eps")
                    {
                        stack_.push_back(transvec.at(k).pushing);
                        future<bool> t = async(launch::async, &PDA::machine, this,  transvec.at(k).Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                        stack_.pop_back();
                    }
                    else{

                        future<bool> t = async(launch::async, &PDA::machine, this,  transvec.at(k).Qf, input_, transitions_, stack_);
                        if(t.get())
                            return true; //if it accepted return true;
                    }
                }

                transitions_.pop_back();
            }
            return false;
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
                cout << "[PDA]: TRANSITION: " << transitions_.at(j).Qs << " " << transitions_.at(j).e << " -> " << transitions_.at(j).Qf <<endl;
                cout << "[PDA]: .." << endl;
            }
            return true;  //if end state is final accept
        }
    }
    return false; //else reject
}
