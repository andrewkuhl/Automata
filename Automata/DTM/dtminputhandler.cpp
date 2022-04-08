//
//  dtminputhandler.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#include "dtminputhandler.hpp"

using namespace std;

DTMInputHandler::DTMInputHandler(const char * argv[])
{
    cout << "[InputHandler]: initialized" << endl;
    cout << "[InputHandler]: loading";
    
    args = argv; //copy args
}
DTMInputHandler::~DTMInputHandler()
{
}
void DTMInputHandler::getMS()
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
    ms >> c; //d{
    do
    {
        DTMTransition t;
        ms >> t.Qs; //Qs
        ms >> t.Qf; //Qf
        ms >> t.read; //read
        ms >> c; //arrow
        ms >> c; //write or ,
        if(c == ",")
            t.write = t.read;//write what u read
        else
        {
            t.write = c;//write
            ms >> c;//,
        }
        ms >> t.direction;
        ms >> c; // ; or }
        d_.push_back(t);
    }while(c != "}");
    
    cout << ".";
    ms >> c;
    ms >> q0_;
    ms >> c;
    
    cout << ".";
    ms >> c;// burn qaccept and {
    ms >> qaccept_;
    ms >> c;
    
    cout << ".";
    ms >> c;// burn qaccept and {
    ms >> qreject_;
    ms >> c;
    
    ms.close();
    cout << "\n[InputHandler]: done"<<endl;
}

void DTMInputHandler::getINF()
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
string DTMInputHandler::getInput()
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
