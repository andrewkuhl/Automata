//
//  pdainputhandler.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#include "pdainputhandler.hpp"

using namespace std;

PDAInputHandler::PDAInputHandler(const char * argv[])
{
    cout << "[InputHandler]: initialized" << endl;
    cout << "[InputHandler]: loading";
    
    args = argv; //copy args
}
PDAInputHandler::~PDAInputHandler()
{
}
void PDAInputHandler::getMS()
{
    ms.open(args[1]);//open file to ptr
    
    if (!ms) //if file not opened
    {
        cout << "[InputHandler][ERROR]: couldn't open specifications"
        << endl;//bad path
        exit(1);
    }
    else //else file opened?
    {
        cout << ".";
        //opened file
    }
    cout << ".";
    string c;
    ms >> c;// burn Q and {
    ms >> c;
    while(c != "}")
    {
        Q_.push_back(c); //load Q
        ms >> c;
    }
    cout << ".";
    ms >> c;// burn E and {
    ms >> c;
    while(c != "}")
    {
        E_.push_back(c); //load E
        ms >> c;
    }
    
    cout << ".";
    ms >> c;// burn G and {
    ms >> c;
    while(c != "}")
    {
        G_.push_back(c); //load G
        ms >> c;
    }
    
    cout << ".";
    vector<string> tmp;
    ms >> c;
    do
    {
        ms >> c;
        if(c!="->")
        {
            if(c!= "," && c != "}")
            {
                tmp.push_back(c);
            }
            else{
                PDATransition t;
                t.Qs = tmp.at(0);
                t.Qf = tmp.at(1);
                t.e = tmp.at(2);
                t.popping = tmp.at(3);
                t.pushing = tmp.at(4);
                d_.push_back(t); //load d
                tmp.clear();
            }
        }
    }while(c != "}");
    
    cout << ".";
    ms >> c;
    ms >> q0_;
    ms >> c;
    
    cout << ".";
    ms >> c;// burn F and {
    ms >> c;
    while(c != "}")
    {
        F_.push_back(c); //load F
        ms >> c;
    }
    ms.close();
    cout << "\n[InputHandler]: done"<<endl;
}

void PDAInputHandler::getINF()
{
    cout << ".";
    
    inf.open(args[2]); //open file to ptr
    if (!inf) //if file not load
    {
        cout << "[InputHandler][ERROR]: couldn't open input"
        << endl;//bad path
        exit(1); //exit
    }
    else //file loaded
    {
        cout << ".";
        cout << ".";
        //opened file
    }
    
    string c;
    inf >> c;
    while(c != "}")
    {
        input.push_back(c);
        inf >> c;
    }
    inf.close();
}
string PDAInputHandler::getInput()
{
    if(input.empty()) //if no more input
    {
        return "";
    }
    else
    {
        string a = input.front(); //pop first string off and return it
        input.erase(input.begin());
        return a;
    }
}
