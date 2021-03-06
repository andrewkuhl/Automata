//
//  dfainputhandler.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#include "dfainputhandler.hpp"

using namespace std;

DFAInputHandler::DFAInputHandler(const char * argv[])
{
    cout << "[InputHandler]: initialized" << endl;
    cout << "[InputHandler]: opening machine specifications.." << endl;
    
    args = argv; //copy args
}
DFAInputHandler::~DFAInputHandler()
{
}
void DFAInputHandler::getMS()
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
        cout << "[InputHandler]: opened specifications" << endl;
        cout << "[InputHandler]: ready.." << endl;
        //opened file
    }
    cout << "[InputHandler]: loading Q" << endl;
    string c;
    ms >> c;// burn Q and {
    ms >> c;
    while(c != "}")
    {
        Q_.push_back(c); //load Q
        ms >> c;
    }
    cout << "[InputHandler]: loading E" << endl;
    ms >> c;// burn E and {
    ms >> c;
    while(c != "}")
    {
        E_.push_back(c); //load E
        ms >> c;
    }
    cout << "[InputHandler]: loading d" << endl;
    vector<string> tmp;
    ms >> c;
    do
    {
        ms >> c;
        if(c!= "," && c != "}")
        {
            tmp.push_back(c);
        }
        else{
            DFATransition t;
            t.Qs = tmp.at(0);
            t.e = tmp.at(1);
            t.Qf = tmp.at(2);
            d_.push_back(t); //load d
            tmp.clear();
        }
    }while(c != "}");
    
    cout << "[InputHandler]: loading q0" << endl;
    ms >> c;
    ms >> q0_;
    ms >> c;
    
    cout << "[InputHandler]: loading F" << endl;
    ms >> c;// burn F and {
    ms >> c;
    while(c != "}")
    {
        F_.push_back(c); //load F
        ms >> c;
    }
    ms.close();

}

void DFAInputHandler::getINF()
{
    cout << "[InputHandler]: opening input.." << endl;
    
    inf.open(args[2]); //open file to ptr
    if (!inf) //if file not load
    {
        cout << "[InputHandler][ERROR]: couldn't open input"
        << endl;//bad path
        exit(1); //exit
    }
    else //file loaded
    {
        cout << "[InputHandler]: opened input" << endl;
        cout << "[InputHandler]: ready.." << endl;
        //opened file
    }
    
    string c;
    inf >> c;
    inf >> c;
    while(c != "}")
    {
        input.push_back(c);
        inf >> c;
    }
    inf.close();
}
string DFAInputHandler::getInput()
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
